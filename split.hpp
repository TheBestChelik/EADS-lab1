#include "Sequence.hpp"

template <typename Key, typename Info>
void split_pos(const Sequence<Key, Info> &seq, int start_pos, int len1, int len2, int count, Sequence<Key, Info> &seq1, Sequence<Key, Info> &seq2)
{
    typename Sequence<Key, Info>::Iterator it = seq.begin();
    Sequence<Key, Info> new_sequence;

    int current_pos = 0;

    while (current_pos < start_pos && it != seq.end())
    {
        new_sequence.push_back(it.key(), it.info());
        ++it;
        ++current_pos;
    }

    // Copy elements to seq2
    int copied_count = 0;
    bool coping_to_seq1 = true;
    for (int c = 0; c < count; c++)
    {
        while (copied_count < len1)
        {
            seq1.push_back(it.key(), it.info());
            seq.it++;
            copied_count++;
        }
        copied_count = 0;
        while (copied_count < len2)
        {
            seq2.push_back(it.key(), it.info());
            it++;
            copied_count++;
        }
    }

    while (it != seq.end())
    {
        new_sequence.push_back(it.key(), it.info());
        ++it;
    }

    seq = new_sequence;
}