#ifndef FLOOR_H
#define FLOOR_H
#include <string>
struct location{
	int r;
	int c;
};

class Floor{
	private:
		location size;
		std::string* rows;
		char** tiles;
	public:
		Floor();
		~Floor();
		Floor(const Floor &f);
		char** getBoard();
		void clearArray();
		void updateRow(std::string, int);
		void updateArray();
		void updateSize(std::string);
		void setTile(int ,int, char);
		std::string getRow(int) const;
		char getTile(int, int) const;
		location getSize() const;
		void print();
		void printRows();
};
#endif