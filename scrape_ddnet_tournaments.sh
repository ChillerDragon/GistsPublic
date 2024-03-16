#!/bin/bash
# reverse engineering the tournaments file
# by parsing the ddnet website
# https://github.com/ddnet/ddnet-scripts/blob/cfd5aceb35a0a82c16eae5ea9061d2a185d781ed/servers/scripts/tournaments.py#L29
# 
# expected output:
# 2022-03-13|#60|60/|Brutal|4|Simple Down|Zweitleben
# 2022-02-22|Tutorial|59/|Novice|1|Tutorial|unique2
# 2021-06-19|#58|58/|Brutal|2|Teetrader|SickCunt
# 2021-05-16|#57|57/|Brutal|1|Bollermann|Cøke
# ..

while read -r line
do
	# mapName (we only want originalMapName)
	# grep blockreleases tourn.html | head -n1 | grep -oE 'id="[^"]+"' | cut -d '"' -f2 | cut -d '-' -f2

	orginalMapName="$(echo "$line" | grep -oE 'Map size: [0-9]+x[0-9]+">[^<]+</span></a></h3><p class="inline"><strong>by <a href="/mappers/' | cut -d '>' -f2- | rev | cut -c 64- | rev)"
	link="$(echo "$line" | grep -oE 'href="[^"]+"' | head -n1 | cut -d '"' -f2)"
	tournament="$(echo "$line" | grep -oE '<a href="[^"]+">[^:]+' | head -n1 | cut -d '>' -f2-)"
	server="$(echo "$line" | grep -oE '<a href="[^"]+">[^<]+ Server' | head -n1 | cut -d':' -f2 | cut -c 2- | rev | cut -c 8- | rev)"
	date="$(echo "$line" | grep -oE '>[0-9]{4}(-[0-9]{2}){2}</h3' | cut -c 2- | rev | cut -c 5- | rev)"
	stars="$(echo "$line" | grep -oE 'Difficulty: [^,]+' | cut -d ' ' -f2 | grep -o '★' | wc -l)"
	mapperName="$(echo "$line" | grep -oE '>by <a href="/mappers/[^>]+>[^<]+' | cut -d '>' -f3)"

	printf '%s|%s|%s|%s|%s|%s|%s\n' \
		"$date" "$tournament" "$link" "$server" "$stars" "$orginalMapName" "$mapperName"

done < <(curl --silent "https://ddnet.tw/tournaments/" | grep blockreleases)
