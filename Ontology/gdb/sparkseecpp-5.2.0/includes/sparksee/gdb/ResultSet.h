/*
 * SPARKSEE: a library for out-of-core graph-based data storage and query processing.
 *
 * See the file LICENSE.txt for redistribution information.
 *
 * Copyright (c) 2005-2010 Sparsity Technologies, Barcelona (Spain)
 */

#ifndef _SPARKSEE_RESULTSET_H_
#define _SPARKSEE_RESULTSET_H_

/**
 * \addtogroup gdb
 * @{
 *
 * \file ResultSet.h
 * \brief It contains the definition of ResultSet class.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */

#include "gdb/Handler.h"
#include <map>

/*
 * Forward declaration of sparksee_core classes.
 */
namespace sparksee_core
{
    class ResultSet;
}

BEGIN_SPARKSEE_GDB_NAMESPACE

/*
 * Forward declaration of sparksee classes.
 */
class ResultSetListIterator;
class Value;

/**
 * \brief ResultSet class.
 *
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT ResultSet
: private Handler<sparksee_core::ResultSet>
{
    friend class Query; // to access private constructor
    friend class StreamQuery; // to access private constructor
    
public:
    
    /**
     * \brief Destructor.
     */
    virtual ~ResultSet();
    
    /**
     * \brief Gets the number of columns.
     *
     * Columns are in the range [0...COLUMNS).
     *
     * \return The number of columns.
     */
    int32_t GetNumColumns() const;
    
    /**
     * \brief Gets the name for the given column.
     * \param index [in] Column index.
     * \return Column name.
     */
    const std::wstring & GetColumnName(int32_t index) const;
    
    /**
     * \brief Gets the column index for the given column name.
     * \param name [in] Column name.
     * \return Column index.
     */
    int32_t GetColumnIndex(const std::wstring & name) const;
    
    /**
     * \brief Gets the datatype for the given column.
     * \param index [in] Column index.
     * \return DataType for the given column.
     */
    DataType GetColumnDataType(int32_t index) const;
    
    /**
     * \brief Fetches the next row.
     *
     * A ResultSet cursor is initially positioned before the first row;
     * the first call to the method "Next" makes the first row the current row;
     * the second call makes the second row the current row, and so on.
     *
     * \return TRUE if the next row has been successfully fetched,
     * FALSE otherwise.
     * \exception QueryException If a database access error occurs.
     */
    bool_t Next();
    
    /**
     * \brief Gets the value for the given column.
     * \param index [in] Column index.
     * \param value [in|out] Value.
     * \exception QueryException If a database access error occurs.
     */
    void GetColumn(int32_t index, Value & value) const;
    
    /**
     * \brief Gets the value for the given column.
     * \param index [in] Column index.
     * \return The Value of the given column.
     * \exception QueryException If a database access error occurs.
     */
    Value * GetColumn(int32_t index) const;
    
    /**
     * \brief Positions the cursor before the first row.
     */
    void Rewind();
    
    /**
     * \brief Returns rows in JSON format
     *
     * Rows are returned from the current position.
     *
     * \param rows [in] Maximum number of rows
     * \return JSON representation of the next <rows> rows in the resultset
     */
    const std::wstring GetJSON(int32_t rows) const;
    
private:
    
    /**
     * \brief Creates a new instance.
     * \param core_query [in] Handled dexcore ResultSet reference.
     * \param sequential [in] It is owned by the creator and cannot be rewinded
     */
    ResultSet(sparksee_core::ResultSet * core_result, bool_t sequential);
    
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    ResultSet(const ResultSet & query);
    
    /**
     * \brief Closes the iterator.
     */
    void Close();

    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    ResultSet & operator =(const ResultSet & query);
    
    /**
     * \brief Column names.
     */
    std::map<std::wstring, int32_t> names;
    
    /**
     * \brief Column indexes.
     */
    std::vector<std::wstring> indexes;
    
    /// denotes if there is a row available after a Next()
    bool_t m_row;
    
    /// true if has external owner and it is forward-only
    bool_t m_sequential;
    
    /// gets the value for a column
    Value* GetColumnValue(int32_t index, Value* ps) const;
};


/**
 * \brief ResultSet list.
 *
 * It stores a ResultSet list.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT ResultSetList
{
    friend class StreamQuery; // to add new elements
    
public:
    
    /**
     * \brief Number of elements in the list.
     * \return Number of elements in the list.
     */
    int32_t Count() const;
    
    /**
     * \brief Constructor.
     *
     * This creates an empty list.
     */
    ResultSetList();
    
    /**
     * \brief Destructor
     */
    ~ResultSetList();
    
    /**
     * \brief Clears the list.
     */
    void Clear();
    
    /**
     * \brief Returns the ResultSet at the specified position in the list.
     * \param index [in] Index of the element to return, starting at 0.
     */
    ResultSet* Get(int32_t index) const;
    
    /**
     * \brief Gets a new ResultSetListIterator.
     * \return ResultSetListIterator instance.
     */
    ResultSetListIterator * Iterator();
    
private:
    
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    ResultSetList(const ResultSetList & sl);
    
    /**
     * \brief Non implemented to avoid use of asignment operator.
     */
    ResultSetList & operator =(const ResultSetList & sl);
    
    /**
     * \brief Adds a ResultSet to the end of the list.
     *
     * It does not make a copy.
     *
     * \param re [in] The ResultSet to add
     */
    void Add(ResultSet * rs);
    
    /**
     * \brief ResultSet list.
     */
    std::vector<ResultSet*> list;
};


/**
 * \brief ResultSetList iterator class.
 *
 * Iterator to traverse all the values into a ResultSetList instance.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT ResultSetListIterator
{
    friend class ResultSetList; // to access private constructor
    
private:
    
    /**
     * \brief std vector iterator.
     */
    std::vector<ResultSet*>::iterator it;
    
    /**
     * \brief Ending std vector iterator.
     */
    std::vector<ResultSet*>::iterator end;
    
    /**
     * \brief Creates a new instance.
     * \param list List to iterate.
     */
    ResultSetListIterator(std::vector<ResultSet*> & list);
    
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    ResultSetListIterator(const ResultSetListIterator & sli);
    
    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    ResultSetListIterator & operator =(const ResultSetListIterator & sli);
    
public:
    
    /**
     * \brief Destructor
     */
    ~ResultSetListIterator();
    
    /**
     * \brief Moves to the next element.
     * \return The next element.
     */
    const ResultSet* Next();
    
    /**
     * \brief Gets if there are more elements.
     * \return TRUE if there are more elements, FALSE otherwise.
     */
    bool_t HasNext();
};



END_SPARKSEE_GDB_NAMESPACE

/** @} */
#endif // _SPARKSEE_RESULTSET_H_
