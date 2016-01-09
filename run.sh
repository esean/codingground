#!/bin/bash

die() { echo "ERROR:$0:$@ !" >&2; exit 1; }
proc() {
	echo "$1"
	pushd $1
	make > README.md || die "Couldnt build $1"
	echo "-----------------------------------" >> README.md
	echo >> README.md
	echo -e "$1:\nExpected output:\n" >> README.md
	./main | awk '{printf("%s\n\n",$0);}' >> README.md
	svn add README.md
	rm main
	popd
}

for i in *; do
	[ -d $i ] && {
		proc $i
	}
done
