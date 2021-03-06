#include "jpeg.h"
#include "kmeans.h"

#include <iostream>
#include "boost/filesystem.hpp"

using namespace std;
//using namespace boost::filesystem;


int clusterImages(boost::filesystem::path p)
{
  using namespace marengo::jpeg;
  boost::filesystem::directory_iterator end_itr;
  string current_file;
  for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
  {
      // If it's not a directory, list it. If you want to list directories too, just remove this check.
      if (boost::filesystem::is_regular_file(itr->path())) {
          // assign current file name to current_file and echo it out to the console.
          current_file = itr->path().string();
      //Image imgOriginal( argv[1] );
      Image imgOriginal(current_file);

      // Copy construct a second version so we can
      // shrink non-destructively. Not really necessary
      // here, but just to show it can be done :)
      Image img = imgOriginal;

      // Shrink proportionally to a specific width (in px)
      img.shrink( 60 );

      // Display the image in ASCII, just for fun.
      std::size_t height = img.getHeight();
      std::size_t width  = img.getWidth();
      // Pixel "Size" is 3 bytes for colour images (i.e. R,G, & B)
      // and 1 byte for monochrome.
      ofstream myfile;
      myfile.open ("1.txt");
      for (std::size_t i = 0; i < width; i ++)
      {
          for (std::size_t j = 0; j < height; j++)
          {
              std::vector<uint8_t> vec = img.getPixel( i, j );
              for (uint8_t k : vec)
              {
                  myfile << (int) k <<" ";
                  //std::cout << (int) k << " "; std::cout.flush();
              }
              myfile << "\n";

              //std::cout << std::endl;
          }
      }
      myfile.close();
      //std::cout << "\nImage px sz : " << img.getPixelSize();
      //std::cout << std::endl;
      int K = 1;

      //Open file for fetching points
      string filename = "1.txt";
      ifstream infile(filename.c_str());

      if(!infile.is_open()){
          cout<<"Error: Failed to open file."<<endl;
          return 1;
      }

      //Fetching points from file
      int pointId = 1;
      vector<Point> all_points;
      string line;

      while(getline(infile, line)){
          Point point(pointId, line);
          all_points.push_back(point);
          pointId++;
      }
      infile.close();
      //cout<<"\nData fetched successfully!"<<endl<<endl;

      //Return if number of clusters > number of points
      if(all_points.size() < K){
          cout<<"Error: Number of clusters greater than number of points."<<endl;
          return 1;
      }

      //Running K-Means Clustering
      int iters = 100;

      KMeans kmeans(K, iters);
      kmeans.run(all_points);
    }
  }
  return 0;
}

int main( int argc, char* argv[] )
{

    try
    {
        // Constructor expects a filename to load:
        
        ofstream outfile;
        outfile.open("clusters.txt", std::ios_base::app);
        if(outfile.is_open())
        {
          outfile<<"Cat\n";
        }
        outfile.close();
        boost::filesystem::path p ("images/cat");
        int res = clusterImages(p);
        outfile.open("clusters.txt", std::ios_base::app);
        if(outfile.is_open())
        {
          outfile<<endl;
          outfile<<"Car\n";
        }
        outfile.close();
        p  = "images/car";
        res = clusterImages(p);
        outfile.open("clusters.txt", std::ios_base::app);
        if(outfile.is_open())
        {
          outfile<<endl;
          outfile<<"Flower\n";
        }
        outfile.close();
        p  = "images/flower";
        res = clusterImages(p);
    }
    catch( const std::exception& e )
    {
        std::cout << "Main() error handler: ";
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
