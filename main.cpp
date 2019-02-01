//
//  main.cpp
//  assignment4
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

/**helper method for checking double values whether equal or not **/
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
        return isinf(slope2) && areSame(slope1, 0.0);
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
void classifyShape(std::vector<std::pair<int, int> >& shape){
    //getting the math attributes of this shape:
    std::vector<double> slopes = shapeSlopes(shape);
    std::vector<double> lengths = shapeLengths(shape);
    std::vector<double> diagonals = shapeDiagonal(shape);
    
    //pass shape's geometric attributes to different shapes' boolean function:
    if(isParallelogram(slopes[0], slopes[1], slopes[2], slopes[3])){
        if (isRhombi(diagonals[0], diagonals[1]) && isRectangle(slopes[0], slopes[1])) {
            std::cout << "square" << std::endl;
        }else if (isRhombi(diagonals[0], diagonals[1])){
            std::cout << "rhombus" << std::endl;
        }else if (isRectangle(slopes[0], slopes[1])){
            std::cout << "rectangle" << std::endl;
        }else{
            std::cout << "parallelogram" << std::endl;
        }
    }else{
        if(isTrapezoid(slopes[0], slopes[1], slopes[2], slopes[3])){
            std::cout << "trapezoid" << std::endl;
        }else if(isKite(lengths[0], lengths[1], lengths[2], lengths[3])){
            std::cout << "kite" << std::endl;
        }else{
            std::cout << "quadrilateral" << std::endl;
        }
    }
}

/**helper method for parsing read-in string**/
std::vector<std::string> stringToArr(std::string& line){
    std::vector<std::string> ret;
    std::string value;
    char delimiter = ' ';
    std::istringstream stream(line);
    
    while (getline(stream, value, delimiter)) {
        ret.push_back(value);
    }
    return ret;
}

bool isError1(std::vector<std::string> strArr){
    //    error1: input number of element not 6
    if(strArr.size() != 6){
        return true;
    }
    //    error1: input contains invalid char
    for(std::string s: strArr){
        for(char c: s){
            if(!isdigit(c)){return true;}
        }
        //        error1: number value out of range
        int num = stoi(s);
        if(num > 100 || num < 0){
            return true;
        }
    }
    return false;
}

/**helper method for checking whether two points coincide**/
bool isSame(std::pair<int, int>& lhs, std::pair<int, int>& rhs){
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}

bool isError2(std::vector<std::pair<int, int> > shape){
    sort(shape.begin(), shape.end());
    
    for(int i = 0; i < shape.size() - 1; i ++){
        if(isSame(shape[i], shape[i+1])){
            return true;
        }
    }
    return false;
}

//cited from : https://stackoverflow.com/questions/14176776/find-out-if-2-lines-intersect
bool isIntersect(std::pair<int, int>& p1, std::pair<int, int>& p2, std::pair<int, int>& q1, std::pair<int, int>& q2){
    return (((q1.first-p1.first) * (p2.second-p1.second) - (q1.second-p1.second)*(p2.first-p1.first))
            * ((q2.first-p1.first) * (p2.second-p1.second) - (q2.second-p1.second)*(p2.first-p1.first)) < 0)
    &&
    (((p1.first-q1.first)*(q2.second-q1.second) - (p1.second-q1.second)*(q2.first-q1.first))
     * ((p2.first-q1.first)*(q2.second-q1.second) - (p2.second-q1.second)*(q2.first-q1.first)) < 0);
}

bool isError3(std::vector<std::pair<int, int> >& shape){
    return isIntersect(shape[0], shape[1], shape[2], shape[3]) || isIntersect(shape[0], shape[3], shape[2], shape[1]);
}

//cite from: https://stackoverflow.com/questions/3813681/checking-to-see-if-3-points-are-on-the-same-line
//[ Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By) ] / 2
bool isError4(std::vector<std::pair<int, int> >& shape){
    bool situation1 = (shape[0].first * (shape[1].second - shape[2].second) + shape[1].first * (shape[2].second - shape[0].second)
                       + shape[2].first * (shape[0].second - shape[1].second)) == 0;
    bool situation2 = (shape[1].first * (shape[2].second - shape[3].second) + shape[2].first * (shape[3].second - shape[1].second)
                       + shape[3].first * (shape[1].second - shape[2].second)) == 0;
    return situation1 || situation2;
}

void mainClassifier(){
    std::string line;
    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        
        if(isError1(stringToArr(line))){
            std::cout << "error1" << std::endl;
            exit(0);
        }else{
            std::vector<std::pair<int, int> > shape;
            shape.push_back(std::make_pair(0,0));
            int x,y;
            while(ss >> x >> y){
                std::pair<int, int> vertice = std::make_pair(x,y);
                shape.push_back(vertice);
            }
            if(isError2(shape)){
                std::cout << "error2" << std::endl;
                exit(0);
            }else if (isError3(shape)){
                std::cout << "error3" << std::endl;
                exit(0);
            }else if(isError4(shape)){
                std::cout << "error4" << std::endl;
                exit(0);
            }else{
                classifyShape(shape);
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    mainClassifier();
}


