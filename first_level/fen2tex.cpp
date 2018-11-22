#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

typedef std::map<std::string, std::string> keymap;

const std::string tpl_start = "\\chessboard[\n\\diagramsize,\nsetfen=",
    tpl_end = ",\nshowmover=true]";

void build_keys(keymap& keys, int argc, char** argv);

void info();
void print_nr_columns(std::ostream& out, size_t n){
	size_t i = 0;
	out << "{";
	while(i != n){
		out << " c";
		++ i;
	}
	out << " }\n";
}

void print_conditions(std::ostream& out, size_t n){
	size_t i = 0;
	while(i != n){
		out << "\\diagramcount\\hspace{3cm}\\textbf{\\#1} ";
		++ i;
		if(i != n) out << "& ";
	}
	out << " \\\\\n";
}

void print_rules(std::ostream& out, size_t n){
	size_t i = 0;
	while(i != n){
		out << "\\rule{4cm}{0.4pt} ";
		++ i;
		if(i != n) out << "& ";
	}
	out << "\\\\\n";
}

int main(int argc, char** argv) {
    keymap keys;
    size_t nr_cols = 3,
    	nr_rows = 4;

    if (argc < 2) {
        std::cout << "no params transmited" << std::endl;
        info();
        return 1;
    }

    build_keys(keys, argc, argv);

    std::string infilename("input.txt");
    std::string outfilename("output.tex");

    if (keys.find("--i") != keys.end()) {
        infilename = keys["--i"];
    }

    if (keys.find("--o") != keys.end()) {
        outfilename = keys["--o"];
    }
    if (keys.find("--cols") != keys.end()) {
        nr_cols = atoi(keys["--cols"].c_str());
    }
    if (keys.find("--rows") != keys.end()) {
        nr_rows = atoi(keys["--rows"].c_str());
    }
    std::string line;

	std::ifstream fin;
	std::ofstream fout;
	try{
		fin.open(infilename.c_str());
    	fout.open(outfilename.c_str(), std::ios::app);    
	}
	catch(std::exception e){
		info();
		return -1;
    }
    std::string tmp;
    size_t col = 0, row = 0;
    size_t counter = 0;
    
    while(!fin.eof()) {
    	std::getline(fin, line);
        if (line.empty()){ continue; }
        ++counter;
		row = ((counter-1) % (nr_cols*nr_rows)) / nr_cols;
		col = (counter-1) % nr_cols;
		std::cout << "row = " << row << ", col = " << col << std::endl;
		
		// page preparing
    	if(row == 0 && col == 0){
    		fout << "\\begin{tabular}";
    		print_nr_columns(fout, nr_cols);
    	}

        if(col != 0) fout << " &\n";
        tmp = tpl_start + line + tpl_end;
        fout << tmp << std::endl;
        if(col == nr_cols-1){
        	fout << " \\\\\n";
        }
        
        if(col == nr_cols-1){
        	print_conditions(fout, nr_cols);
            // print_rules(fout, nr_cols);
        }

        if(col == nr_cols-1 && row ==nr_rows-1){
			fout << "\\end{tabular}\n\\newpage\n";
    	}		
    }
    if((col+1)*(row+1) != nr_cols*nr_rows) {
       	// print_conditions(fout, nr_cols);
        // print_rules(fout, nr_cols);
    	fout << "\\end{tabular}";
    }
    
    fout.close();
    fin.close();
    return 0;
}


void info() {
	std::cout << "using:\n";
	std::cout << "\tfen2tex - types this info\n";
	std::cout << "\tfen2tex [--i=<INPUTFILE>] [--o=OUTPUTFILE] [--cols=<NR_COLS>] [--rows=NR_ROWS]\n";
	std::cout << "\t\tINPUTFILE -- input file, implicitly is `input.txt`";
	std::cout << "\t\tOUTPUTFILE -- output file, implicitly is `output.tex`";
	std::cout << "\t\tNR_COLS -- number of diagrams in row (nr of columns) per page, implicitly is 3";
	std::cout << "\t\tNR_ROWS -- number of diagrams in column (nr of rows) per page, implicitly is 4";
}

void build_keys(keymap& keys, int argc, char** argv) {
    int i, tmp;
    std::string key, value, aux;
    for (i = 0; i != argc; ++i) {
        aux = std::string(argv[i]);
        tmp = aux.find('=');
        if (tmp != aux.npos) {
            key = aux.substr(0, tmp);
            value = aux.substr(tmp+1, aux.size() - tmp - 1);
            keys[key] = value;
        }
    }
}
