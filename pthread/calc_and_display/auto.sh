

loop=10
mod=10
limit=10000

while sleep 1;
	do 
		clear;
		echo loop: $loop , mod: $mod , limit: $limit;
		./main $loop $mod;
		loop=$((loop*2));
		if ((loop > limit));then
			break;
		fi
	done