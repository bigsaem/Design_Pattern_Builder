#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct HtmlElement
{
  string name, text;
  vector<HtmlElement> elements;
  const size_t indent_size = 2;
  HtmlElement(){};
  HtmlElement(const string &name, const string &text) : name(name), text(text) {}

  string str(int indent = 0) const {
    cout<<indent<<endl;
    ostringstream oss;
    string i(indent_size* indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (text.size() >0)
      oss <<string(indent_size*(indent +1), ' ')<< text << endl;
    for(const auto& e:elements)
      oss << e.str(indent +1);
    oss <<i << "</" << name << ">" << endl;
    return oss.str();
  }
};

struct HtmlBuilder
{
  HtmlElement root;

  HtmlBuilder (string root_name)
  {
    root.name = root_name;
  }

  void add_child(string child_name, string child_text)
  {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
  }
  void add_child(HtmlElement e)
  {
    root.elements.emplace_back(e);
  }
  string str() const {return root.str();}
};
int main() {
  // the example below is bad
  // it doesn't use oop's feature at all
  auto text= "hello";
  string output;
  output += "<p>";
  output += text;
  output += "</p>";
  cout<<output<<endl;

  string words[] ={"hello", "world"};
  ostringstream oss;
  oss << "<ul>";
  for (auto w : words)
      oss << "  <li>" << w << "</li>";
  oss << "</ul>";
  cout << oss.str() << endl;

  // so we use builder to make it more scalable and simple
  HtmlBuilder builder{"ul"};
  HtmlElement child {"li", "I'm a child"};
  child.elements.push_back(HtmlElement{"li", "I'm a grandchild"});
  child.elements.emplace_back("li", "I'm a grandchild");
  builder.add_child("li", "hello");
  builder.add_child("li", "hello");
  builder.add_child(child);
  cout << builder.str() <<endl;
  return 0;
}
