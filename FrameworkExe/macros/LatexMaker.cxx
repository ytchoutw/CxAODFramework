#include "LatexMaker.h"

#include "Utils.h"

#include <TString.h>

#include <fstream>
#include <iostream>

LatexMaker::LatexMaker() {

}

LatexMaker::~LatexMaker() {

  for(unsigned int i=0; i<m_slidesVec.size(); i++) {
    delete m_slidesVec[i];
  }
  m_slidesVec.clear();
  m_slidesMap.clear();
}

void LatexMaker::addFigure(std::string fileName, std::string sectionTitle,
			   std::string slideTitle, std::string caption, int order) {

  Figure figure;
  figure.caption = caption;
  figure.fileName = fileName;

  std::map<std::string, Slide*>::iterator slideItr = m_slidesMap.find(slideTitle);
  if(slideItr == m_slidesMap.end()) {
    Slide *slide = new Slide;
    slide->title = slideTitle;
    slide->sectionTitle = sectionTitle;
    slide->order = order;
    slide->type = 1;
    slide->figures.push_back(figure);

    insertSlide(slide);
  }else{
    slideItr->second->figures.push_back(figure);
  }

}

void LatexMaker::addTableColumn(std::string sectionTitle, std::string slideTitle, std::string columnTitle, 
				std::vector<std::string> rowNames, 
				std::vector<double> values) {

  std::map<std::string, Slide*>::iterator slideItr = m_slidesMap.find(slideTitle);
  if(slideItr == m_slidesMap.end()) {

    Slide *slide = new Slide;
    slide->title = slideTitle;
    slide->sectionTitle = sectionTitle;
    slide->type = 0;
    slide->order = 0;

    Figure figure;
    figure.caption = "";

    figure.rowNames = rowNames;
    figure.rows.resize(rowNames.size());
    for(unsigned int row=0; row<rowNames.size(); row++) {
      figure.rows[row].push_back(values[row]);
    }
    figure.colNames.push_back(columnTitle);

    slide->figures.push_back(figure);

    insertSlide(slide);

  }else{

    for(unsigned int row=0; row<rowNames.size(); row++) {
      slideItr->second->figures[0].rows[row].push_back(values[row]);
    }
    slideItr->second->figures[0].colNames.push_back(columnTitle);
  }

}
void LatexMaker::insertSlide(Slide *slide) {

  std::vector<Slide*>::iterator slideItr = m_slidesVec.begin();
  for(; slideItr!=m_slidesVec.end(); slideItr++) {
    if(slide->type < (*slideItr)->type) break;
    if(slide->order < (*slideItr)->order) break;
  }
  m_slidesVec.insert(slideItr, slide);

  m_slidesMap.insert(std::make_pair(slide->title, slide));
}

void LatexMaker::makeLatex(std::string fileName) {

  std::ofstream ofile (fileName.c_str(), std::ios::out);

  std::string sectionTitle = "";

  for(unsigned int i=0; i<m_slidesVec.size(); i++) {
    
    Slide slide = *(m_slidesVec[i]);

    if(slide.sectionTitle != sectionTitle) {

      sectionTitle = slide.sectionTitle;

      ofile << std::endl
	    << "\\subsection{" << sectionTitle << "}"
	    << std::endl;
    }

    if(slide.type == 1) {

      int nfig = slide.figures.size();
      
      int ncol = (int)(sqrt(nfig)+1.5);
      int nrow = ncol-1;
      
      int prod = ncol * nrow;
      
      int step = 0;
      while(prod >= nfig) {
	step ++;
	if(step % 2 == 0) nrow--;
	else ncol--;
	prod = ncol * nrow;
      }
      if(step % 2 == 0) nrow++;
      else ncol++;
      
      double width = 0.9 / ncol;
      double height = 0.8 / nrow;
      
      int ifig = 0;    
      
      ofile << std::endl
	    << "\\begin{frame}{" << getLatexFriendly(slide.title) << "}" << std::endl;
      
      for(int row=0; row<nrow; row++) {
	
	ofile << "  \\begin{columns}[c]" << std::endl;
	
	for(int col=0; col<ncol; col++) {
	  
	  ofile << "    \\column{" << width << "\\linewidth}" << std::endl
		<< "    \\centering\\includegraphics[width=\\textwidth]{" << slide.figures[ifig].fileName << "}\\\\" << std::endl
		<< "    " << getLatexFriendly(slide.figures[ifig].caption)  << std::endl;
	  
	  ifig++;
	  if(ifig >= nfig) break;
	}
	ofile << "  \\end{columns}" << std::endl;
	if(ifig >= nfig) break;
      }
      
      ofile << "\\end{frame}" << std::endl
	    << std::endl;

    } else {

      Figure figure = slide.figures[0];
     
      int ncol = figure.colNames.size();
      int nrow = figure.rowNames.size();
  
      ofile << std::endl
	    << "\\begin{frame}{" << getLatexFriendly(slide.title) << "}" << std::endl
	    << "\\begin{center}" << std::endl
	    << "  \\begin{tabular}{l";
      for(int col=0; col<ncol; col++) {
	ofile << "| >{\\centering\\let\\newline\\\\\\arraybackslash\\hspace{0pt}}m{1.4cm}";
      }
      ofile << "}" << std::endl
	    << "    ";
      for(int col=0; col<ncol; col++) {
	ofile << "& " << getLatexFriendly(figure.colNames[col]) << " ";
      }
      ofile << "\\\\" << std::endl
	    << " \\hline \\hline"
	    << std::endl;

      for(int row=0; row<nrow; row++) {
	ofile << "    " << getLatexFriendly(figure.rowNames[row]);
	for(int col=0; col<ncol; col++) {
	  ofile << "& " << TString::Format("%.3g", figure.rows[row][col]) << " ";
	}
	ofile << "\\\\" << std::endl
	      << " \\hline"
	      << std::endl;
      }

      ofile << "  \\end{tabular}" << std::endl
	    << "\\end{center}" << std::endl
	    << "\\end{frame}" << std::endl
	    << std::endl;
    }
  }
}

std::string LatexMaker::getLatexFriendly(std::string phrase) {

  Utils::replaceAll(phrase, "_", "\\_");
  Utils::replaceAll(phrase, "#Delta", "$\\Delta$");
  Utils::replaceAll(phrase, "#phi", "$\\phi$");
  Utils::replaceAll(phrase, "p\\_{T}^{V}", "$p_T^V$");
  Utils::replaceAll(phrase, "\\_min", "$_{min}$");
  Utils::replaceAll(phrase, "b\\_1", "$b_1$");
  Utils::replaceAll(phrase, "b\\_2", "$b_2$");
  Utils::replaceAll(phrase, "m\\_T", "$m_T$");

  return phrase;
}
