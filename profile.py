import os
import filecmp


os.system("rm ./testCase/*")
os.system("rm ./coverage/*")
os.system("rm ./output/*")
os.system("rm ./raw/*")
os.system("clang++ -c main.cpp")
os.system("clang++ -o main main.o")
os.system("python3 fuzz.py")
os.system("clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main")



directory = os.fsencode("testCase")
	

for file in os.listdir(directory):
	filename = os.path.splitext(os.fsdecode(file))[0]

	# print(filename)
	os.system("LLVM_PROFILE_FILE=" + "raw/"+filename + ".profraw " + "./main" + "< ./testCase/" + filename +".txt" + " > ./coverage/" + filename +".txt")

prefix = "xcrun llvm-profdata merge -sparse"

directory1 = os.fsencode("raw")
for file in os.listdir(directory1):
	filename = os.path.splitext(os.fsdecode(file))[0]
	# compare supposed correct output with current print one:
	if filecmp.cmp("./coverage/" + filename + ".txt", "./output/" + filename + ".txt"):
		print("fix bug " + filename)
		
	prefix += " " + "raw/"+filename + ".profraw"
	# print(prefix)

mergeData = prefix + " -o main.profdata"
os.system(mergeData)


# os.system("xcrun llvm-profdata merge -sparse file000.profraw file001.profraw file002.profraw file003.profraw file004.profraw file005.profraw -o main.profdata")
# print("here")
os.system("xcrun llvm-cov report ./main -instr-profile=main.profdata")





