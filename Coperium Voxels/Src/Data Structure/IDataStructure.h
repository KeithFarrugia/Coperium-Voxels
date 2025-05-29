#ifndef I_DATASTRUCTURE_H
#define I_DATASTRUCTURE_H

// A minimal abstract interface for our data structures.
template <typename id_type, typename data_type>
class IDataStructure {
public:
    virtual ~IDataStructure() = default;

    // Inserts an element. Returns a pointer to the data stored at the key.
    virtual data_type* Insert(const id_type& id, const data_type& data) = 0;

    // Removes an element with the given key.
    virtual void Remove(const id_type& id) = 0;

    // Returns a pointer to the data stored at the key (or nullptr if not found).
    virtual data_type* Find(const id_type& id) const = 0;

    // Clears the entire container.
    virtual void Clear() = 0;
};

#endif // I_DATASTRUCTURE_H
