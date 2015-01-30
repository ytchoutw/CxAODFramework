#ifndef LATEXMAKER_H
#define LATEXMAKER_H

#include <string>
#include <map>
#include <vector>

class LatexMaker {

public:
  LatexMaker();
  ~LatexMaker();

  void addFigure(std::string fileName, std::string sectionTitle,
		 std::string slideTitle, std::string caption, int order=0);
  void addTableColumn(std::string sectionTitle,
		      std::string slideTitle, std::string columnTitle, 
		      std::vector<std::string> rowNames, 
		      std::vector<double> values);

  void makeLatex(std::string fileName);

private:

  struct Figure {
    std::string caption;
    std::string fileName;
    std::vector<std::string> rowNames;
    std::vector<std::string> colNames;
    std::vector<std::vector<double> > rows;
  };

  struct Slide {
    std::string title;
    std::string sectionTitle;
    int order;
    int type; // 0 table ; 1 figure
    std::vector<Figure> figures;
  };

  std::string getLatexFriendly(std::string phrase);
  void insertSlide(Slide *slide);

  std::map<std::string, Slide*> m_slidesMap;
  std::vector<Slide*> m_slidesVec;
};

#endif
