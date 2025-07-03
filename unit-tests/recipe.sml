Name: 'Opal.UnitTests'
Language: 'C++|0'
Version: 1.0.0
Type: 'Executable'
Source: [
	'gen/Main.cpp'
]
IncludePaths: [
	'./'
]
Dependencies: {
	Runtime: [
		'mwasplund|Soup.Test.Assert@0'
		'../Source/'
	]
}