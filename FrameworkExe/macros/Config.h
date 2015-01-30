#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <map>

class Config {

public:

  // Samples
  enum SampleType {
    Data,
    Signal,
    Background,
    DummySample
  };
  struct Sample {
    SampleType type;
    std::string name;
    std::string title;
    int fillColor;
    int lineColor;
    int markerColor;
    int stackIndex;
  };

  void addSample(SampleType type, 
		 std::string name,
		 std::string title, 
		 int fillColor,
		 int lineColor,
		 int markerColor,
		 int stackIndex);

  void addBackgroundSample(std::string name, std::string title, int color, double scaleFactor);
  void addSignalSample(std::string name, std::string title, int color, double scaleFactor);
  void addBackgroundSample(std::string name, std::string title, int color);
  void addSignalSample(std::string name, std::string title, int color);
  void addDataSample(std::string name, std::string title, int color);
  void setTotalBackgroundName(std::string name);

  struct ScaleFactor {
    std::string sample;
    std::string regionExp;
    double value;
  };
  
  void addScaleFactor(std::string sample, std::string regionExp, double value);
  double getScaleFactor(std::string sample, std::string region);

  void readScaleFactors(std::string sfFileName);

  int getNSamples();
  Sample getSample(int i);
  std::vector<Sample> getSamples();
  std::string getTotalBackgroundName();
  bool canUseTotalBackground();
  int getBkgCount();
  int getSigCount();

  void setLegendThreshold(double threshold);
  double getLegendThreshold();

  void setNoStack(bool noStack=true);
  bool getNoStack();

  void setMake1DPlots(bool make1D=true);
  bool getMake1DPlots();

  void setMake2DPlots(bool make2D=true);
  bool getMake2DPlots();

  void setOverwrite(bool overwrite=true);
  bool getOverwrite();

  // Analysis
  enum AnalysisType {
    ZeroLepton,
    OneLepton,
    TwoLepton,
    DummyAnalysis
  };
  struct Analysis {
    AnalysisType type;
    std::string status;
    std::string name;
    std::string CME;
    std::string luminosity;
    std::string mH;
    std::string institute;
    std::string version;
    std::string inputPath; 
    std::string inputFile;
    std::string inputTDirectory;
    std::string outputPath;
  };

  void setAnalysis(AnalysisType type,
		   std::string status,
		   std::string name,
		   std::string CME,
		   std::string luminosity,
		   std::string mH,
		   std::string institute,
		   std::string version);
  void setInputPath(std::string inputPath);
  void setInputFile(std::string inputFile);
  void setInputTDirectory(std::string inputDir);
  void setOutputPath(std::string outputPath);
  std::string getInputFileFullName(std::string trafo);
  std::string getInputTDirectory();
  std::string getAnalysisStatus();
  std::string getCME();
  std::string getLuminosity();
  std::string getAnalysisTitle();
  std::string getOutputPath();

  // BDT transformation
  struct BDTTransform {
    std::string name;
    int method;
    float par1;
    float par2;
  };
  BDTTransform makeBDTTransformation(std::string name, 
				     int method=0, float par1=0, float par2=0);
  void addBDTTransformation(std::string name, int method=0, float par1=0, float par2=0);
  std::vector<BDTTransform> getBDTTransformations();

  // Blinding
  enum BlindingType {
    Threshold,
    Window,
    DummyBlinding
  };
  struct Blinding {
    BlindingType type;
    double threshold;
    std::string varName;
    std::string region;
    std::string trafo;
    double xmin;
    double xmax;
  };
  void setThresholdBlinding(double blinding);
  void addWindowBlinding(std::string varName, std::string region, std::string trafo, double xmin, double xmax);

  int getNBlindings();
  Blinding getBlinding(int i);
  std::vector<Blinding> getBlindings();

  // variables
  enum VariableType {
    BDTInput,
    BDTOutput,
    DummyVariable
  };
  struct Variable {
    VariableType type;
    std::string name;
    std::string title;
    double xmin;
    double xmax;
    int ngroup;
    double xscale;
    bool equidist;
    bool relabel;

  };

  void addVariable( VariableType type,
		    std::string name,
		    std::string title,
		    double xmin=-1,
		    double xmax=-1,
		    int ngroup =-1,
		    double xscale=1.,
		    bool equidist=true,
		    bool relabel=false);

  int getNVariables();
  Variable getVariable(int i);
  std::vector<Variable> getVariables();

  // Control regions
  struct Region {
    std::string name;
    std::string groupName;
    std::string title;
    std::string slideTitle;
    std::vector<Region*> subRegions;
  };
  void clearRegions();
  void addRegion(std::string name, std::string title, std::string slideTitle);
  void addRegion(std::string name, std::string groupName, std::string title, std::string slideTitle);

  int getNRegions();
  Region *getRegion(int i);
  std::vector<Region*> getRegions();

  // systematics
  struct Systematic {
    std::string name;
    bool isOneSided;
  };

  void clearSystematics();
  void addSystematic(std::string name, bool isOneSided);
  int getNSystematics();
  Systematic getSystematic(int i);
  std::vector<Systematic> getSystematics();

  // SystematicPlot 
  struct SystematicPlot {
    bool isDummy;
    std::string var;
    std::string region;
    std::string trafo;
    std::string slideTitle;
  };
  SystematicPlot getDetailedSystematicsPlots(std::string varName, std::string trafoName, std::string regionName);
  void addDetailedSystematicsPlots(std::string varName, std::string trafoName, std::string regionName, std::string slideTitle);

  // histogram naming convention
  std::string getHistoName(std::string dir, std::string sample, std::string region, std::string var, std::string sys);

  // sensitivity plots
  struct SensitivityPlot {
    std::string name;
    std::string var;
    std::string region;
    std::string trafo;
  };
  std::vector<std::string> getSensitivityPlots(std::string var, std::string region, std::string trafo);
  void addSensitivityPlot( std::string name, std::string var, std::string region, std::string trafo="");

  // Other setup
  void readSetup();

  // error check
  bool isValid();

  Config();
  ~Config();

private:

  std::vector<Sample> m_samples;
  std::vector<ScaleFactor> m_scaleFactors;
  std::string m_totalBkgName;
  int m_bkgCount;
  int m_sigCount;
  Analysis m_analysis;
  std::vector<Variable> m_variables;
  std::map<std::string, Region*> m_regionsMap;
  std::vector<Region*> m_regions;
  std::vector<Systematic> m_systematics;
  std::vector<SystematicPlot> m_systPlots;
  std::vector<BDTTransform> m_BDTTransformations;
  std::vector<Blinding> m_blindings;
  std::vector<SensitivityPlot> m_sensitivityPlots;
  double m_legendThreshold;
  bool m_make1DPlots;
  bool m_make2DPlots;
  bool m_noStack;
  bool m_overwrite;

  bool m_isValid;
};

#endif
