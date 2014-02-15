vector<list<int>> CreateGraph( const list<pair<int,int>*>& List, bool *mass, int Size)
{
    vector<list<int>> Vertical;
    Vertical.reserve(Size);
    for ( auto it: List)
    {
        if(!Vertical[it->first].size())
        {
            Vertical[it->first].push_back(it->second);
        }
        else
        {
            list<int> tmp;
            tmp.push_back(it->second);
            Vertical[it->first] = tmp;
        }
    }
    return Vertical;
}
