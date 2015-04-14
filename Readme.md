## Serial Wire Debug (SWD) Analyzer for Saleae Logic ##

### Todo

* Simulation Data!

* Packets that end after ack
* Annotate turnarounds
* List things? Jtag analyser does it

### Build instructions

* Download and extract the Saleae [Analyzer SDK](http://support.saleae.com/hc/en-us/articles/201104644-Analyzer-SDK).
* If running on linux amd64, replace `lib/libAnalyzer.so` in the SDK with the `libAnalyzer.so` that is shipped with Logic itself (the SDK only seems to contain the 32 bit version).
* Clone this repository into a subdirectory of the SDK.
* Inside the clone, run `make`.
* Copy `release/libSWDAnalyzer.so` into Logic's `Analyzers` directory.
