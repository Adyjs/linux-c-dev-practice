

loop=10
mod=10
limit=100000000

while sleep 1;
	do 
		./main $loop $mod;
		loop=$((loop*2));
		if ((loop > limit));then
			break;
		fi
	done