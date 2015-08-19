#ifndef GETTER_H
#define GETTER_H

namespace getter
{

#define GETTER(A, b) [](const A& a) { return a.b; }

} // namespace getter


#endif // GETTER_H
