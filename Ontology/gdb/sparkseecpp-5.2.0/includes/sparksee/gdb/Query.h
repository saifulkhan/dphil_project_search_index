/*
 * SPARKSEE: a library for out-of-core graph-based data storage and query processing.
 *
 * See the file LICENSE.txt for redistribution information.
 *
 * Copyright (c) 2005-2010 Sparsity Technologies, Barcelona (Spain)
 */

#ifndef _SPARKSEE_QUERY_H_
#define _SPARKSEE_QUERY_H_

/**
 * \addtogroup gdb
 * @{
 *
 * \file Query.h
 * \brief It contains the definition of Query class.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */

#include "gdb/Value.h"

#include <map>

/*
 * Forward declaration of sparksee_core classes.
 */
namespace sparksee_core
{
    class Query;
}

BEGIN_SPARKSEE_GDB_NAMESPACE

/*
 * Forward declaration of sparksee classes.
 */
class ResultSet;
class ResultSetList;
class StreamQuery;

/**
 * \brief Query stream interface.
 *
 * A QueryStream is the interface between the application and the
 * STREAM operator. When the operator starts inside a Query, the
 * method is prepared with query-defined arguments. Then, if there
 * are input operations, the STREAM operator builds the ResultSets
 * and starts the iteration. Finally, the operator fetches
 * rows until no more are available.
 *
 * Application exceptions must be cached by the subclass
 * that implements the interface.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT QueryStream
{
public:
    
    /**
     * \brief Destructor.
     */
    virtual ~QueryStream();
    
    /**
     * \brief Prepares the stream before it is started.
     *
     * \param list [in] Optional list of arguments
     * \return FALSE on error
     */
    virtual bool_t Prepare(const ValueList& list) = 0;
    
    /**
     * \brief Starts the stream.
     *
     * \param list [in] Optional list of input ResultSets
     * \return \a FALSE on error
     */
    virtual bool_t Start(ResultSetList& list) = 0;
    
    /**
     * \brief Gets the next row and moves the iterator forward
     *
     * The end of sequence is denoted by returning TRUE with
     * an empty row. A valid row must contain as many
     * values (even NULL) as expected by the query.
     *
     * \param list [out] Storage for the new rows
     * \return TRUE if there is a row or end of sequence,
     *         FALSE on error
     */
    virtual bool_t Fetch(ValueList& list) = 0;
    
protected:
    /**
     * \brief Default constructor
     */
    QueryStream();
    
private:
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    QueryStream(const QueryStream & query);
    
    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    QueryStream & operator =(const QueryStream & query);
};

/**
 * \brief Query class.
 *
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT Query
: private Handler<sparksee_core::Query>
{
    friend class Session; // to access private constructor
    friend class QueryContext; // to access private constructor
    
public:
    
    /**
     * \brief Destructor.
     */
    virtual ~Query();

    /**
     * \brief Executes the given statement.
     *
     * \param stmt [in] Query statement.
     * \return A ResultSet instance with the contents of the result of the query.
     */
    ResultSet * Execute(const std::wstring & stmt);
    
    /**
     * Sets a query stream handler
     *
     * Query streams handlers are created and destroyed by the caller.
     *
     * \param stream [in] The stream name
     * \param handler [in] Query stream handler
     * \returns The previous handler, or NULL if it does not exists
     */
    QueryStream * SetStream(const std::wstring &stream, QueryStream * handler);
    
    /**
     * Sets the value for a dynamic paramater
     *
     * \param name [in] Parameter name
     * \param value [in] Parameter value
     */
    void SetDynamic(const std::wstring &name, Value& value);
    
private:
    
    /**
     * \brief Creates a new instance.
     * \param core_query [in] Handled dexcore Query reference.
     */
    Query(sparksee_core::Query * core_query);
    
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    Query(const Query & query);
    
    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    Query & operator =(const Query & query);

    /**
     * \brief Query stream handlers
     */
    std::map<std::wstring, StreamQuery*> streams;
};

END_SPARKSEE_GDB_NAMESPACE

/** @} */
#endif // _SPARKSEE_QUERY_H_
