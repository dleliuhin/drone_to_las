#!/bin/bash

./scripts/refresh.sh

SEARCH_STRING=$1
REPLACE_STRING=$2
PREVIEW_FLAG=$3

[[ -z $SEARCH_STRING ]] && echo -e "\e[44mEmpty arg SEARCH_STRING\e[0m" && exit 1 
[[ -z $REPLACE_STRING ]] && echo -e "\e[44mEmpty arg REPLACE_STRING\e[0m" && exit 1

[[ $PREVIEW_FLAG != "--preview" ]] && sed_arg="-i"

file_list=''

file_list=$(grep -RHIn --exclude-dir="external" --exclude-dir=".git" "$SEARCH_STRING" ./ | \
	grep -v "doxygen" | \
	grep -v ".git*" | \
	awk '{print $1}' | \
	sed "s/:.*//g" | \
	uniq)

for file_name in $file_list; do
	[[ $PREVIEW_FLAG == "preview" ]] && echo -en "\e[43m$file_name\e[0m\n"
	sed $sed_arg "s/$SEARCH_STRING/$REPLACE_STRING/g" $file_name | grep $REPLACE_STRING
done

echo "Replacement from $SEARCH_STRING to $REPLACE_STRING done"

mv cfg/$1.cfg cfg/$2.cfg

