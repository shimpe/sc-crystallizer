Crystallizer : UGen {
	*ar { |input, mult = 0|
		^this.multiNew('audio', input, mult);
	}
	
	checkInputs {
		
        if (rate == 'audio' and: {inputs.at(0).rate != 'audio'}, {
            ^("input must be audio rate signal!" + inputs.at(0) + inputs.at(0).rate);
        });
        
		^this.checkValidInputs;
	}
}
