# put in 2D list

def quote_fix(line):
	# find locations in strings with open quotes, and convert next comma to an underscore
	quote = line.find("\"")
	# replace next comma with an underscore
	return line[:quote] + line[quote:].replace(",","_",1)
	
def csv_to_2d(name):
	file = open(name, "r")
	labels = file.readline().split(",")
	return [dict(zip(labels, quote_fix(line).split(","))) for line in file]
	
arr = csv_to_2d("sample_dataset.csv")
for don in arr:
	if 'memo_text' in don:
		print(don['memo_text'])
