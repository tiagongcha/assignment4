//
//  main.cpp
//  assignment3
//
//  Created by Gong Tia on 1/17/19.
//  Copyright © 2019 Gong Tia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>

/**Check double values whether equal or not **/
bool areSame(double a, double b){
    return std::fabs(a + - b) < std::numeric_limits<double>::epsilon();
}

/**get the slope of a line**/
double getSlope(std::pair<int, int> point1, std::pair<int, int> point2){
    int xDiff = point1.first - point2.first;
    int yDiff = point1.second - point2.second;
    if(xDiff == 0)
        return std::numeric_limits<double>::infinity();
    return yDiff/ (double)xDiff;
}

/**get the distance of two points**/
double getLength(std::pair<int, int> point1, std::pair<int, int> point2){
    int sum = pow((point1.first - point2.first), 2) + pow((point1.second - point2.second), 2);
    return sqrt((double)sum);
}

/**Check whether two lines are vertical**/
bool isVertical(double slope1, double slope2){
    if(isinf(slope1) || isinf(slope2)){
        if(isinf(slope1) && isinf(slope2)){
            return false;
        }else{
            return (isinf(slope1) && areSame(slope2, 0.0)) || (isinf(slope2) && areSame(slope1, 0.0));
        }
    }else{
        return areSame(slope1 * slope2, -1);
    }
}

/**Check whether two lines are paralle**/
bool isParalle(double slope1, double slope2){
    if(isinf(slope1) || isinf(slope2)){
        return isinf(slope1) && isinf(slope2);
    }else{
        return areSame(slope1 , slope2);
    }
}

/**Check if it is parallelograms**/
bool isParallelogram(double slope1, double slope2, double slope3, double slope4){
    return isParalle(slope1, slope3) && isParalle(slope2, slope4);
}

/**Check if it is Rhombi**/
bool isRhombi(double diagonal1, double diagonal2){
    return isVertical(diagonal1, diagonal2);
}

/**Check if it is Rectangle**/
bool isRectangle(double slope1, double slope2){
    return isVertical(slope1, slope2);
}

/**Check if it is Trapezoid**/
bool isTrapezoid(double slope1, double slope2, double slope3, double slope4){
    return isParalle(slope1, slope3) || isParalle(slope2, slope4);
}

/**Check if it is kite**/
bool isKite(double length1, double length2, double length3, double length4){
    return areSame(length1, length2) || areSame(length2, length3) || areSame(length3, length4);
}

/**Get the 4 slopes of this shape's lines**/
std::vector<double> shapeSlopes(std::vector<std::pair<int, int> > &shape){
    std::vector<double> slopes;
    slopes.push_back(getSlope(shape[1], shape[0]));
    slopes.push_back(getSlope(shape[2], shape[1]));
    slopes.push_back(getSlope(shape[3], shape[2]));
    slopes.push_back(getSlope(shape[0], shape[3]));
    return slopes;
}

/**Get the lengths of each line of this shape**/
std::vector<double> shapeLengths(std::vector<std::pair<int, int> > &shape){
    std::vector<double> lengths;
    lengths.push_back(getLength(shape[1], shape[0]));
     lengths.push_back(getLength(shape[2], shape[1]));
     lengths.push_back(getLength(shape[3], shape[2]));
     lengths.push_back(getLength(shape[0], shape[3]));
    return lengths;
}

/**Get the two diagonals' slopes of this shape**/
std::vector<double> shapeDiagonal(std::vector<std::pair<int, int> > &shape){
    std::vector<double> diagonals;
    diagonals.push_back(getSlope(shape[2], shape[0]));
    diagonals.push_back(getSlope(shape[3], shape[1]));
    return diagonals;
}

/**This method takes in the coordinates of a shape's four points, classifying their specific shape, and write to the output file**/
void classifyShape(std::vector<std::pair<int, int> >& shape, std::ofstream& outfile){
    //getting the math attributes of this shape:
    std::vector<double> slopes = shapeSlopes(shape);
    std::vector<double> lengths = shapeLengths(shape);
    std::vector<double> diagonals = shapeDiagonal(shape);
    
    //pass shape's geometric attributes to different shapes' boolean function:
    if(isParallelogram(slopes[0], slopes[1], slopes[2], slopes[3])){
        if (isRhombi(diagonals[0], diagonals[1]) && isRectangle(slopes[0], slopes[1])) {
            outfile << "square" << std::endl;
        }else if (isRhombi(diagonals[0], diagonals[1])){
            outfile << "rhombus" << std::endl;
        }else if (isRectangle(slopes[0], slopes[1])){
            outfile << "rectangle" << std::endl;
        }else{
            outfile << "parallelogram" << std::endl;
        }
    }else{
        if(isTrapezoid(slopes[0], slopes[1], slopes[2], slopes[3])){
            outfile << "trapezoid" << std::endl;
        }else if(isKite(lengths[0], lengths[1], lengths[2], lengths[3])){
            outfile << "kite" << std::endl;
        }else{
            outfile << "quadrilateral" << std::endl;
        }
    }
}

void mainClassifier(std::string inFileName, std::string outFileName){
    std::ifstream infile;
    std::ofstream outfile;
    infile.open(inFileName);
    outfile.open(outFileName);
    
    std::string line;
    while(std::getline(infile, line)){
        std::stringstream ss(line);
        std::vector<std::pair<int, int> > shape;
        shape.push_back(std::make_pair(0,0));
        
        int x,y;
        while(ss >> x >> y){
            std::pair<int, int> vertice = std::make_pair(x,y);
            shape.push_back(vertice);
        }
        classifyShape(shape, outfile);
    }
    infile.close();
    outfile.close();
}


int main(int argc, const char * argv[]) {
   mainClassifier("shapes.txt", "shapesout.txt");
    return 0;
}

