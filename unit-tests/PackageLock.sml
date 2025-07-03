Version: 5
Closures: {
	Root: {
		'C++': {
			Opal: { Version: '../Source/', Build: 'Build0', Tool: 'Tool0' }
			'Opal.UnitTests': { Version: './', Build: 'Build0', Tool: 'Tool0' }
			'mwasplund|Soup.Test.Assert': { Version: '0.4.1', Build: 'Build0', Tool: 'Tool0' }
		}
	}
	Build0: {
		Wren: {
			'mwasplund|Soup.Cpp': { Version: '0.12.0' }
		}
	}
	Tool0: {
		'C++': {
			'mwasplund|copy': { Version: '1.1.0' }
			'mwasplund|mkdir': { Version: '1.1.0' }
		}
	}
}