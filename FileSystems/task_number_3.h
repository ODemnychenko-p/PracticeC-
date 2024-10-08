//
// Created by O.Demnychenko on 10/9/2024.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void remove_empty_lines(const fs::path& filepath)
{
    std::ifstream filein(filepath.native(), std::ios::in);
    if(!filein.is_open())
    {
        throw std::runtime_error("cannot open input file");
    }

    auto temppath = fs::temp_directory_path() / "temp.txt";
    std::ofstream fileout(temppath.native(), std::ios::out | std::ios::trunc);
    if(!fileout.is_open())
    {
        throw std::runtime_error("cannot create temporary file");
    }
    std::string line;
    while(std::getline(filein, line))
    {
        if(line.length() > 0 && line.find_first_not_of(' ') != line.npos)
        {
            fileout << line << '\n';
        }
    }

    filein.close();
    fileout.close();

    fs::remove(filepath);
    fs::rename(temppath, filepath);
}

static void task_number_3()
{
    std::string path;
    std::cin >> path;

    remove_empty_lines(path);
}