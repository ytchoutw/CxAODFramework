Skeleton example of making an EL:Algorithm to make a really flat mini-tuple.

How to configure the TupleMaker
===============================

The TupleMaker has the following *required* configuration items:

string TupleMaker.MuonsIn
string TupleMaker.ElectronsIn
string TupleMaker.JetsIn
string TupleMaker.Label

These tell the TupleMaker the names of the containers to look for in the input xAOD file for Muons, electrons and jets respectively.

The label is used to define the stream for the output.

For example if you run with the output path as submitDir then the tuple will appear in the submitDir/data-<label> directory

where <label> is the value of TupleMaker.Label

The TupleMaker has 3 optional configuration items:

( [] = default setting)

vector<string> TupleMaker.Variations [empty]
string TupleMaker.VariationMode ["none"]
bool TupleMaker.UseEventInfo [false]


Variations is a list of systematic names. This should just be a total list of systematics - not broken down by collection type, the code will automatically figure out from the first event processed which variations are present for which collections. There are two "special" reserved values that can be used here:

Original : this is used to specify that the DxAOD containers should be used rather than the "Nominal" ones from the CxAOD

Nominal : this is used to specify that the "Nominal" containers should be used

So to output the original and calibrated collections you might specify:

vector<string> TupleMaker.Variations = Original Nominal

(this of course assumes that the collections actually exist in the input file - at the moment the original containers are not copied to the CxAOD)

To output the original, calibration and the EG_SCALE_ALL__1down variation you would write:

vector<string> TupleMaker.Variations = Original Nominal EG_SCALE_ALL__1down

VariationMode indicates how the TupleMaker should handle processing of the variations. There are currently 4 valid values for this:

"none" : don't do any variations - in this case the list of variations, if it exists, will be ignored and the code will first search for the appropriate container containing exactly the name specified in the configuration file, and then if that fails will search for the container with that name with "___Nominal" appended. If both those searches fail, the job will fail.

"file" : this will create a different output stream and corresponding tuple for each variation specified in the variation list. The output trees have the same format. Where a specific variation does not exist for a given collection - the nominal values will be written to the file

"tree" : this will create one output stream but with one tree per variation.

"block" : this will create one output stream and one tree but with one block of variables in the output for each variation for example:

 jet_Nominal_pt
 jet_EG_SCALE_ALL__1down_pt

This last mode might be most useful for debugging problems with the calibration tools but is not forseen to be useful in normal analysis running.

