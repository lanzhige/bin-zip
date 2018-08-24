/*
*program to compress and decompress the segmented binary files
*/
#include <ctime>

#include<iostream>
#include<experimental/filesystem>

#include "compression.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

using std::string;
namespace fs = std::experimental::filesystem;

// load the file directories and compress or decompress the file in the folder\
 zip_flag 0 means to compress, zip_flag 1 means to decompress.
int recLoad(const string &input, const string &output, int zip_flag = 0) {
	fs::path filepath(input);
	fs::path outpath(output);
	if (filepath == outpath) {
		std::cerr << "illegal file input or output path, file overwrite may occur!" << std::endl;
		exit(1);
	}
	int res = 0;
	std::clock_t start = std::clock();
	double duration;
	std::cout << "start processing folder: " << input << std::endl;
	for (auto &dir : fs::directory_iterator(filepath)) {
		if (fs::is_directory(dir)) {
			string cur_dir = input + "\\" + dir.path().filename().string();
			string out_dir = output + "\\" + dir.path().filename().string();
			fs::create_directories(out_dir);
			recLoad(cur_dir, out_dir, zip_flag);
		} else {
			string cur_dir = dir.path().string();
			string out_dir = output + "\\" + dir.path().filename().string();
			FILE *fin = fopen(&cur_dir[0], "rb");
			FILE *fo = fopen(&out_dir[0], "wb+");
			if (zip_flag) {
				inf(fin, fo);
			}
			else {
				def(fin, fo, Z_DEFAULT_COMPRESSION);
			}
			fclose(fin);
			fclose(fo);
			res++;
		}
	}
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "finish processing folder: " << input << " time spent: " << duration << " seconds." << std::endl << std::endl;
	return res;
}

bool confirm(const string &input, const string &output, int flag) {
	if (flag) {
		std::cout << "Decompress files in root folder: " << input << " into root folder: " << output << "? [y/n]" << std::endl;
		string s;
		std::cin >> s;
		if (s == "yes" || s == "y" || s == "YES" || s == "Y") return true;
		return false;
	}
	else {
		std::cout << "Compress files in root folder: " << input << " into root folder: " << output << "? [y/n]" << std::endl;
		string s;
		std::cin >> s;
		if (s == "yes" || s == "y" || s == "YES" || s == "Y") return true;
		return false;
	}
}

int main(int argc, char** argv){
	switch(argc){
	case 1: {
		FILE *fp;
		if ((fp = fopen("./config.ini", "r")) != NULL) {
			char buff[255];
			fscanf(fp, "%s", buff);
			string input(buff);
			fscanf(fp, "%s", buff);
			string output(buff);
			int flag;
			fscanf(fp, "%d", &flag);
			if (confirm(input, output, flag)) {
				recLoad(input, output, flag);
			}
			fclose(fp);
		}
		else {
			std::cerr << "not enough parameters or ./config.ini not fount!" << std::endl;
			exit(1);
		}
		break;
	}
	case 2: {
		string input(argv[1]);
		fs::path inpath(input);
		string output = inpath.parent_path().string() + "\\" + inpath.filename().string() + "_compressed";
		if (confirm(input, output, 0)) {
			recLoad(input, output, 0);
		}
		break;
	}
	case 3: {
		string input(argv[1]);
		string output(argv[2]);
		if (confirm(input, output, 0)) {
			recLoad(input, output, 0);
		}
		break;
	}
	case 4: {
		if (argv[1][0] == '-') {
			if (argv[1][1] == 'c') {
				string input(argv[2]);
				string output(argv[3]);
				if (confirm(input, output, 0)) {
					recLoad(input, output, 0);
				}
			}
			else if (argv[1][1]=='d'){
				string input(argv[2]);
				string output(argv[3]);
				if (confirm(input, output, 1)) {
					recLoad(input, output, 1);
				}
			}
			else {
				std::cout << "for 3 parameters, the first one should be -c for compress and -d for decompress" << std::endl;
			}
		}
		else {
			std::cout << "for 3 parameters, the first one should be -c for compress and -d for decompress" << std::endl;
		}
		break;
	}
	default:
		std::cerr<<"err: undefined number of command line parameters!"<<std::endl;
	}
	return 0;
}