import sys

def triangle(n, m): # calculates triangular number from two given values
    return int(n*(n+1)/2 - 1 + m)

def parse_headers(line:str):
    epochs = {} # dict with key=epoch/0 for sv, value=index in a row
    for i, item in enumerate(line):
        if (item in ['g/h', 'm', 'n']): # skip first three items
            continue
        else:
            try:
                epochs[int(float(item))] = i # epochs
            except:
                epochs[0] = i # secular var
    return epochs

def make_coeffs(epochs:dict, nepochs=14): # populates coeffs dict
    coeffs = {}
    for epoch in epochs.keys():
        coeffs[epoch] = [[0, 0] for i in range(triangle(nepochs-1, nepochs-1) + 1)]
    return coeffs

def get_data(line:list, epochs:dict, coeffs:dict):
    idx_gh = 0 if line[0] == 'g' else 1
    n = int(line[1])
    m = int(line[2])
    for year in epochs.keys():
        idx_year = epochs[year]
        value = float(line[idx_year])
        coeffs[year][triangle(n, m)][idx_gh] = value  

def format_comm_str(epochs:int):
    comm_str = " " * 11
    comm_str += "//"
    for n in range(1, epochs + 1):
        for m in range(0, epochs + 1):
            if (m > n):
                continue
            str_temp = "{0} {1} ".format(n, m)
            comm_str += " " * (11 - len(str_temp))
            comm_str += str_temp
    comm_str += "\n"
    return comm_str
def format_coeffs(coeffs:list):
    n_str = "    /* g */ {"
    m_str = "    /* h */ {"
    for i, (n, m) in enumerate(coeffs):
        n_str += "{:10.2f}".format(n)
        m_str += "{:10.2f}".format(m)
        n_str += "," if (i != len(coeffs)-1) else "},\n"
        m_str += "," if (i != len(coeffs)-1) else "}\n"
    return format_comm_str(13) + n_str + m_str

if __name__ == '__main__':
    try:
        if (len(sys.argv) != 3):
            raise Exception("Wrong number of arguments: 3 required")
        
        ifile = sys.argv[1]
        ofile = sys.argv[2]
        
        epochs = dict()
        coeffs = dict()
        
        # read coeff file
        with open(ifile, 'r') as f:
            lines = f.readlines()
            are_epochs = False
            for line in lines:
                line = line.split(' ')
                line = [elem.rstrip() for elem in line if elem != '']
                if (line[0] == 'g/h'):
                    epochs = parse_headers(line)
                    coeffs = make_coeffs(epochs, 14)
                    are_epochs = True
                if (are_epochs & (line[0] in ['g', 'h'])):
                    get_data(line, epochs, coeffs)
        # write coeff.hpp file
        with open(ofile, 'w') as f:
            f.write("#pragma once\n#include <map>\n#include <vector>\n\n")
            f.write("struct GH_vals {\n")
            f.write("    std::vector<double> g;\n    std::vector<double> h;\n};\n")
            f.write("using Coeffs = std::map<int, GH_vals>;\n\n")
            f.write("namespace igrf::constants {\n")
            f.write("    const Coeffs COEFFS = {\n")
            epochs = coeffs.keys()
            for i, epoch in enumerate(epochs):
                padding_epoch = " " * 8
                epochs_str = padding_epoch + "{" + str(epoch) + ", GH_vals {\n";
                epochs_str += format_coeffs(coeffs[epoch])
                epochs_str += padding_epoch
                epochs_str += "}},\n" if (i != len(epochs) - 1) else "}}\n"
                f.write(epochs_str)
            f.write("    };\n")
            f.write("}")
    except Exception as e:
        print("Something went wrong: " + e.args)

