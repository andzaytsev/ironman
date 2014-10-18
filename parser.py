import json
f = open("log", 'r')

data = {}
for line in f:
	if len(line.split(" "))==3:
		hand, attr, state = line.split(" ")
		if data.get((hand, attr)) is None:
			data[(hand, attr)] = {"max": int(state), "min": int(state)}
		else:
			data[(hand, attr)] = {"max": max(data[(hand, attr)]["max"], int(state)),
			"min": min(data[(hand, attr)]["min"], int(state))}
	if len(line.split(" "))==2:
		hand, motion = line.split(" ")
		if data.get(hand) is None:
			data[hand] = [motion]
		else:
			data[hand].append(motion)

print data
f.close()