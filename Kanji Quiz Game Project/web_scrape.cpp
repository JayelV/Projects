#include"../react.h"

int main() {
  const char *html = _fetch("https://wp.stolaf.edu/");

  // find something in the html, and print it out
  const char *keyword = "c-content-block__desc";
  int index = index_of(html, keyword);
  if (-1 != index) {
    index += length_of(keyword) + 2; // skip the keyword
    string result(html + index, 79); // make length 79
    cerr << result << endl;
  } else {
    cerr << html << endl;
    cerr << "not found in above response." << endl;
  }
}
