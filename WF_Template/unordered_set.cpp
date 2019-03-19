struct Hash
{
	size_t operator()(const int &x) const
	{
		return (size_t)(x);
	}
};
struct Equal
{
	bool operator()(const int &x,const int &y) const
	{
		return x==y;
	}
};
typedef unordered_set<int,Hash,Equal> S;
