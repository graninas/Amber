#ifndef GETTER_H
#define GETTER_H

namespace lenses
{

#define GETTER(A, b) [](const A& a) { return a.b; }


template <typename ST, typename Value, typename Focus>
Focus view(const ST& st, const Value& value)
{

}


} // namespace lenses


#endif // GETTER_H
