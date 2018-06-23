#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



bool isBitSet(char ch, int pos) {
	// 7 6 5 4 3 2 1 0
	ch = ch >> pos;//右移幾個pos
	if(ch & 1)//ch and 1=1?
		return true;
	return false;
}

int main(int argc, char** argv) {

	/*
	./encode image.png textfile.txt output_image.png
	argv[0] = ./encode
	argv[1] = image.png
	argv[2] = textfile.txt
	argv[3] = output_image.png
	*/

	// Checks if proper number of arguments are passed
	if(argc != 3) {
		cout << "Arguments Error" << "\n";
		return 1;
	}

	// Stores original image
	Mat image = imread(argv[1]);
	if(image.empty()) {
		cout << "Image Error\n";
		return 1;
	}

	// Open file for text information
	ifstream file(argv[2]);
	if(!file.is_open()) {
		cout << "File Error\n";
		return 1;
	}

	// char to work on
	char ch;
	// reads the first char from the file
	file.get(ch);
	// contains information about which bit of char to work on
	int bit_count = 0;
	// to check whether file has ended
	bool last_null_char = false;
	// to check if the whole message is encoded or not
	bool encoded = false;

	/*
	To hide text into images. We are taking one char (8 bits) and each of the 8 bits are stored
	in the Least Significant Bits (LSB) of the pixel values (Red,Green,Blue).
	We are manipulating bits in such way that changing LSB of the pixel values will not make a huge difference.
	The image will still look similiar to the naked eye.
	*/
	cout<< image.rows<<"\n";
	cout<< image.cols<<"\n";

	for(int row=0; row < image.rows; row++) {
		for(int col=0; col < image.cols; col++) {
			for(int color=0; color < 3; color++) {
				// stores the pixel details
				Vec3b pixel = image.at<Vec3b>(Point(row,col));//像素

				// if bit is 1 : change LSB of present color value to 1.
				// if bit is 0 : change LSB of present color value to 0.
				if(isBitSet(ch,7-bit_count))
					pixel.val[color] |= 1;
				    //	pixel.val[color] or 1(強制設成1)
				else
					pixel.val[color] &= ~1;//維持原狀

				// update the image with the changed pixel values
				image.at<Vec3b>(Point(row,col)) = pixel;

				// increment bit_count to work on next bit
				bit_count++;

				// 如果讀到文字檔的最後一個字元 則跳出三個迴圈輸出圖片
				if(last_null_char && bit_count == 8) {
					encoded  = true;
					goto OUT;
				}

				// if bit_count is 8 we pick the next char from the file and work on it
				if(bit_count == 8) {
					bit_count = 0;
					file.get(ch);

					// if EndOfFile(EOF) is encountered insert NULL char to the image
					if(file.eof()) {
						last_null_char = true;
						ch = '\0';
					}
				}

			}
		}
	}
	
	OUT:;


	// whole message was not encoded
	if(!encoded) {
		cout << "Message too big. Try with larger image.\n";
		return 2;
	}

	// Writes the stegnographic image
	//imwrite(argv[3],image);
	string output("encode-");
	output =  output +argv[1];
    imwrite(output,image);
    return 0;
}

