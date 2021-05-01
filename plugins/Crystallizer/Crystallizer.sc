Crystallizer : UGen {
	*ar { |input, mult = 0|
		^this.multiNew('audio', input, mult);
	}
	checkInputs {
		[0, 1].do {
			|idx|
			if (rate == 'audio' and: {inputs.at(idx).rate != 'audio'}, {
				^("input must be audio rate signal!" + inputs.at(idx) + inputs.at(idx).rate);
                	});

                };
		^this.checkValidInputs;
	}
}
