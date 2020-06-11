#ifndef _STRUCT_H_
#define _STRUCT_H_

struct coordinate
{
	int x, y;

	bool operator ==(const coordinate& rhs) {
		return (x == rhs.x && y == rhs.y);
	};
	
};

#endif _STRUCT_H_