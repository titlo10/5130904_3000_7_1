#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <limits>
#include <cmath>
#include <numeric>
#include <string>
#include <iomanip>

namespace gubanov
{
  struct Point
  {
    int x, y;

    double getDistance(const Point& point) const
    {
      return std::hypot(x - point.x, y - point.y);
    }

    bool operator !=(const Point& other) const
    {
      return x != other.x || y != other.y;
    }
  };

  double getTriangleArea(const Point& pointFirst, const Point& pointSecond, const Point& pointThird)
  {
    auto a = pointFirst.getDistance(pointSecond),
      b = pointSecond.getDistance(pointThird),
      c = pointFirst.getDistance(pointThird);
    double perimeter = (a + b + c) / 2;
    return sqrt(perimeter * (perimeter - a) * (perimeter - b) * (perimeter - c));
  }

  struct Polygon
  {
    std::vector<Point> points;

    bool operator <(const Polygon& other) const
    {
      return getArea() < other.getArea();
    }

    bool operator==(const Polygon& other) const
    {
      if (points.size() != other.points.size())
      {
        return false;
      }
      for (size_t i = 0; i < points.size(); i++)
      {
        if (points[i] != other.points[i])
        {
          return false;
        }
      }
      return true;
    }

    double getArea() const
    {
      const Point pointFirst = points[0];
      Point prev = points[1];
      return std::accumulate(points.begin() + 2, points.end(), 0.0,
        [&pointFirst, &prev](double accumulatedArea, const Point& current)
        {
          double TriangleArea = getTriangleArea(pointFirst, prev, current);
          accumulatedArea += TriangleArea;
          prev = current;
          return accumulatedArea;
        }
      );
    }
  };

  int convertToNumber(const std::string& str) {
    char* end;
    int res = strtol(str.c_str(), &end, 10);
    if (*end != 0)
    {
      return -1;
    }
    return res;
  }

  void getTotalArea(const std::vector<Polygon>& polygons)
  {
    using namespace std::placeholders;
    std::string argument;
    std::cin >> argument;
    int number = convertToNumber(argument);
    auto accumulatePolygonsArea =
      [&polygons, &number](double accumulatedArea, const Polygon& current, const std::string method)
      {
        double result = accumulatedArea;
        if (method == "EVEN" && current.points.size() % 2 == 0)
        {
          result += current.getArea();
        }
        else if (method == "ODD" && current.points.size() % 2 != 0)
        {
          result += current.getArea();
        }
        else if (method == "MEAN")
        {
          result += current.getArea();
        }
        else if (method == "SPECIAL" && current.points.size() == static_cast<size_t>(number))
        {
          result += current.getArea();
        }
        return result;
      };
    if (number == -1)
    {
      if (argument == "EVEN" || argument == "ODD")
      {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
          std::bind(accumulatePolygonsArea, _1, _2, argument)) << std::endl;
      }
      else if (argument == "MEAN" && polygons.size() != 0)
      {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
          std::bind(accumulatePolygonsArea, _1, _2, argument)) / polygons.size() << std::endl;
      }
      else
      {
        throw "<INVALID COMMAND>";
      }
    }
    else if (number > 2)
    {
      std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(accumulatePolygonsArea, _1, _2, "SPECIAL")) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }

  void calculateMinOrMax(const std::vector<Polygon>& polygons, const std::string& method)
  {
    std::string argument;
    std::cin >> argument;
    if (polygons.size() == 0)
    {
      throw "<INVALID COMMAND>";
    }

    std::vector<size_t> sizeVector(polygons.size());

    std::transform(polygons.begin(), polygons.end(), sizeVector.begin(),
      [](const Polygon& current)
      {
        return current.points.size();
      }
    );
    if (argument == "AREA")
    {
      if (method == "MIN")
      {
        std::cout << std::min_element(polygons.begin(), polygons.end())->getArea() << std::endl;
      }
      else
      {
        std::cout << std::max_element(polygons.begin(), polygons.end())->getArea() << std::endl;
      }
    }
    else if (argument == "VERTEXES")
    {
      if (method == "MAX")
      {
        std::cout << *std::max_element(sizeVector.begin(), sizeVector.end()) << std::endl;
      }
      else
      {
        std::cout << *std::min_element(sizeVector.begin(), sizeVector.end()) << std::endl;
      }
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }

  void countPolygons(const std::vector<Polygon>& polygons)
  {
    using namespace std::placeholders;
    std::string argument;
    std::cin >> argument;
    int number = convertToNumber(argument);
    auto count = [&number](const Polygon& poly, const std::string& method)
      {
        if (method == "EVEN")
        {
          return poly.points.size() % 2 == 0;
        }
        else if (method == "ODD")
        {
          return poly.points.size() % 2 != 0;
        }
        else if (method == "SPECIAL")
        {
          return poly.points.size() == static_cast<size_t>(number);
        }
        return false;
      };
    if (number == -1)
    {
      if (argument == "EVEN" || argument == "ODD")
      {
        std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, argument)) << std::endl;
      }
      else
      {
        throw "<INVALID COMMAND>";
      }
    }
    else if (number > 2)
    {
      std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, "SPECIAL")) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }

  struct DelimeterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char symbol = '0';

    in >> symbol;

    if (in && (symbol != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    in >> DelimeterIO{ '(' } >> point.x >> DelimeterIO{ ';' } >> point.y >> DelimeterIO{ ')' };
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& poly)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    size_t numPoints;

    in >> numPoints;

    if (numPoints < 3)
    {
      in.setstate(std::istream::failbit);
      return in;
    }

    poly.points.clear();
    poly.points.resize(numPoints);

    for (Point& point : poly.points)
    {
      in >> point;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << "(" << point.x << ";" << point.y << ")";
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& poly)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }

    out << poly.points.size() << " ";

    for (const Point& point : poly.points)
    {
      out << point << " ";
    }
    return out;
  }

  struct FrameRectangle
  {
    Point bottom_left;
    Point top_right;
  };

  FrameRectangle getFrameRectangle(const std::vector<Polygon>& polygons)
  {
    FrameRectangle rect;
    rect.bottom_left.x = std::numeric_limits<int>::max();
    rect.bottom_left.y = std::numeric_limits<int>::max();
    rect.top_right.x = std::numeric_limits<int>::min();
    rect.top_right.y = std::numeric_limits<int>::min();
    auto comparatorwithX =
      [](const Point& pointFirst, const Point& pointSecond)
      {
        return pointFirst.x < pointSecond.x;
      };
    auto comparatorwithY =
      [](const Point& pointFirst, const Point& pointSecond)
      {
        return pointFirst.y < pointSecond.y;
      };
    rect = std::accumulate(polygons.begin(), polygons.end(), rect,
      [&](FrameRectangle rect, const Polygon& polygon)
      {
        auto min_x = std::min_element(polygon.points.begin(), polygon.points.end(), comparatorwithX);
        auto min_y = std::min_element(polygon.points.begin(), polygon.points.end(), comparatorwithY);
        auto max_x = std::max_element(polygon.points.begin(), polygon.points.end(), comparatorwithX);
        auto max_y = std::max_element(polygon.points.begin(), polygon.points.end(), comparatorwithY);
        rect.bottom_left.x = std::min(rect.bottom_left.x, min_x->x);
        rect.bottom_left.y = std::min(rect.bottom_left.y, min_y->y);
        rect.top_right.x = std::max(rect.top_right.x, max_x->x);
        rect.top_right.y = std::max(rect.top_right.y, max_y->y);
        return rect;
      }
    );
    return rect;
  }

  void InFrame(const std::vector<Polygon>& polygons)
  {
    Polygon polygon_param;
    std::cin >> polygon_param;
    int ch = std::cin.get();

    while (ch != int('\n') && ch != EOF)
    {
      if (!isspace(ch))
      {
        std::cin.setstate(std::istream::failbit);
        break;
      }
      ch = std::cin.get();
    }

    if (!std::cin)
    {
      std::cin.clear();
      throw "<INVALID COMMAND>";
    }
    FrameRectangle frame = getFrameRectangle(polygons);
    if (std::all_of(polygon_param.points.begin(), polygon_param.points.end(),
      [&frame](const Point& point)
      {
        return point.x >= frame.bottom_left.x && point.x <= frame.top_right.x &&
          point.y >= frame.bottom_left.y && point.y <= frame.top_right.y;
      }))
    {
      std::cout << "<TRUE>\n";
    }
    else
    {
      std::cout << "<FALSE>\n";
    }
  }

  void echo(std::vector<Polygon>& polygons)
  {
    Polygon p;
    std::cin >> p;

    int ch = std::cin.get();

    while (ch != int('\n') && ch != EOF)
    {
      if (!isspace(ch))
      {
        std::cin.setstate(std::istream::failbit);
        break;
      }
      ch = std::cin.get();
    }

    if (!std::cin)
    {
      std::cin.clear();
      throw "<INVALID COMMAND>";
    }
    std::vector<Polygon> result = std::accumulate(polygons.begin(), polygons.end(), std::vector<Polygon>(),
      [&p](std::vector<Polygon> acc, const Polygon& poly)
      {
        if (poly == p)
        {
          acc.push_back(poly);
          acc.push_back(p);
        }
        else
        {
          acc.push_back(poly);
        }
        return acc;
      });
    std::cout << std::count(polygons.begin(), polygons.end(), p) << '\n';
    polygons = result;
  }
}

int main(int argc, char* argv[])
{
  using namespace gubanov;
  if (argc != 2)
  {
    std::cerr << "Error: filename missing\n";
    return EXIT_FAILURE;
  }

  const std::string filename = argv[1];
  std::ifstream file(filename);

  if (!file)
  {
    std::cerr << "Error: file doesn't exists\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<Polygon> fileData;

  while (!file.eof())
  {
    std::copy(std::istream_iterator<Polygon>(file),
      std::istream_iterator<Polygon>(),
      std::back_inserter(fileData));

    if (file.fail() && !file.eof())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    try
    {
      if (command == "AREA")
      {
        getTotalArea(fileData);
      }
      else if (command == "MAX" || command == "MIN")
      {
        calculateMinOrMax(fileData, command);
      }
      else if (command == "COUNT")
      {
        countPolygons(fileData);
      }
      else if (command == "INFRAME")
      {
        InFrame(fileData);
      }
      else if (command == "ECHO")
      {
        echo(fileData);
      }
      else if (command != "")
      {
        throw "<INVALID COMMAND>";
      }
    }
    catch (const char* error)
    {
      std::cout << error << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return EXIT_SUCCESS;
}
