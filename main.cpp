
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

const int ROWS = 11;
const int COLS = 11;

class Tile {
private:
    int index,N, W, E, S;
    Mat image;
public:
    Tile(int indx, Mat img);
    ~Tile();
    void Cardinal(int indx);
    Mat getImg() { return image; };
    int getIndex() { return index; };
    int getN() { return N; };
    int getE() { return E; };
    int getS() { return S; };
    int getW() { return W; };

};

Tile::Tile(int indx, Mat img) {
    index = indx;
    image = img;
    Cardinal(index);
}

Tile::~Tile()
{
}


void Tile::Cardinal(int indx) {
        if (indx >= 8) {
            W = 8;
            indx -= 8;
        }
        else
            W = 0;
        if (indx >= 4) {
            S = 4;
            indx -= 4;
        }
        else
            S = 0;
        if (indx >= 2) {
            E = 2;
            indx -= 2;
        }
        else
            E = 0;
        if (indx >= 1) 
            N = 1;       
        else
            N = 0;   
}

Mat concatenateImages(vector<Tile*> tiles) {

    // Create an empty image to store the concatenated images
    Mat output;
    // Set the width of the output image to the sum of the widths of all images
    //int width = images[0].cols * 4;
    int width = tiles[0]->getImg().cols * ROWS;
    // Set the height of the output image to the sum of the heights of all images
    int height = tiles[0]->getImg().rows * COLS;
    output.create(height, width, tiles[0]->getImg().type());

    // Initialize the x and y positions to 0
    int x = 0;
    int y = 0;
    // Iterate through the images and copy them onto the output image
    for (int i = 0; i < tiles.size(); i++) {
        Mat roi = output(Rect(x, y, tiles[i]->getImg().cols, tiles[i]->getImg().rows));
        tiles[i]->getImg().copyTo(roi);
        // Update the x position for the next image
        x += tiles[i]->getImg().cols;
        // If we have reached the end of the row, reset x and update y
        if (x >= width) {
            x = 0;
            y += tiles[i]->getImg().rows;
        }
    }

    return output;
}

int main(int argc, char** argv)
{
    
    Mat image;
    vector <Tile*> images;
    vector <Tile*> finale;
    int counter = 0;
    int sum;
    int random;
    int chessboard[ROWS][COLS];
    srand(time(0));
    string folder_path = "C:/Users/peter/Desktop/code/c++/semestralka/sprites/roads2W/";

    for (const auto& entry : fs::directory_iterator(folder_path))
    {
        // Check if the file is an image
        if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
        {
            // Load the image
            image = imread(entry.path().string());
            Tile* t = new Tile(counter, image);
            images.push_back(t);
            counter++;
        }
    }

    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            chessboard[i][j] = 99;
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if ((i + j) % 2 == 1) {
                random = rand() % images.size();
                chessboard[i][j] = images[random]->getIndex();
            }
        }
    }


    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if ((i + j) % 2 == 0) {
                sum = 0;
                if (i > 0) {
                    if (images[chessboard[i - 1][j]]->getS() == 4) // top neigbour
                        sum += 1;
                }
                if (i < ROWS - 1) {
                    if (images[chessboard[i + 1][j]]->getN() == 1) // bot neighbour
                        sum += 4;
                }
                if (j > 0) {
                    if (images[chessboard[i][j - 1]]->getE() == 2) // west neighbour
                        sum += 8;
                }                   
                if (j < COLS - 1) {
                    if (images[chessboard[i][j + 1]]->getW() == 8) // east neighbour
                        sum += 2;
                }

                chessboard[i][j] = sum;
            }
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            
            finale.push_back(images[chessboard[i][j]]);
        }
        
    }



    Mat concatenatedImage = concatenateImages(finale);



    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", concatenatedImage);
    imwrite("generated.jpg", concatenatedImage);
    waitKey(0);
    
    return 0;
}