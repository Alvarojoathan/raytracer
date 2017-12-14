#include <cstddef>
#include <array>
#include <fstream>
#include <armadillo>

template <std::size_t SIZE>
using column = std::array<arma::vec, SIZE>;

template <std::size_t WIDTH, std::size_t HEIGHT>
class image {
	column<HEIGHT> *color;

	public:
	image () {
		color = new column<HEIGHT>[WIDTH];
	}

	~image () {
		delete [] color;
	}

	column<HEIGHT>& operator[](std::size_t pos) {
		return color[pos];
	}

	const column<HEIGHT>& operator[](std::size_t pos) const {
		return color[pos];
	}
};

template <std::size_t WIDTH, std::size_t HEIGHT>
void write_pgm (const image<WIDTH, HEIGHT> &img, std::ostream &file) {
	file << "P3" << std::endl;
	file << WIDTH << " " << HEIGHT << std::endl;
	file << "255" << std::endl;

	std::size_t i, j;
	for (j=0; j<HEIGHT; j++) {
		for (i=0; i<WIDTH; i++) {
			arma::vec curr = img[i][j];
			file << curr(0) << " " << curr(1) << " "
					<< curr(2) << " ";
		}
		file << std::endl;
	}
}

template <std::size_t WIDTH, std::size_t HEIGHT>
void render (image<WIDTH, HEIGHT> &img) {
	std::size_t i, j;
	for (i=0; i<WIDTH; i++) {
		for (j=0; j<HEIGHT; j++) {
			if (i < WIDTH / 3) {
				img[i][j] << 0 << 0 << 255;
			} else if (i < 2 * WIDTH / 3) {
				img[i][j] << 255 << 255 << 255;
			} else {
				img[i][j] << 255 << 0 << 0;
			}
		}
	}
}

int main (int argc, char **argv) {
	image<800, 600> img;
	render (img);

	std::ofstream file("out0.pgm");
	write_pgm (img, file);
	file.close();

	return 0;
}
