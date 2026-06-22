#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static bool writeReplaced(std::ofstream& output, const std::string& content,
	const std::string& s1, const std::string& s2)
{
	std::string::size_type start = 0;
	std::string::size_type found;

	found = content.find(s1, start);
	while (found != std::string::npos)
	{
		output << content.substr(start, found - start) << s2;
		start = found + s1.length();
		found = content.find(s1, start);
	}
	output << content.substr(start);
	return output.good();
}

int main(int argc, char** argv)
{
	std::ifstream input;
	std::ofstream output;
	std::ostringstream buffer;
	std::string outputName;

	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>"
			<< std::endl;
		return 1;
	}
	if (argv[2][0] == '\0')
	{
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return 1;
	}
	input.open(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Error: cannot open input file" << std::endl;
		return 1;
	}
	buffer << input.rdbuf();
	if (input.bad())
	{
		std::cerr << "Error: cannot read input file" << std::endl;
		return 1;
	}
	outputName = std::string(argv[1]) + ".replace";
	output.open(outputName.c_str());
	if (!output.is_open())
	{
		std::cerr << "Error: cannot create output file" << std::endl;
		return 1;
	}
	if (!writeReplaced(output, buffer.str(), argv[2], argv[3]))
	{
		std::cerr << "Error: cannot write output file" << std::endl;
		return 1;
	}
	return 0;
}
