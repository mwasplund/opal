Name: 'opal-unit-tests'
Language: 'C++|0'
Version: 1.0.0
Type: 'Executable'
Source: [
	'gen/main.cpp'
]
IncludePaths: [
	'./'
]
Dependencies: {
	Runtime: [
		'mwasplund|soup-test-assert@0'
		'../source/'
	]
}