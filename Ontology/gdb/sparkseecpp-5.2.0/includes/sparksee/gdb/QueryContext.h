/*
 * SPARKSEE: a library for out-of-core graph-based data storage and query processing.
 *
 * See the file LICENSE.txt for redistribution information.
 *
 * Copyright (c) 2005-2010 Sparsity Technologies, Barcelona (Spain)
 */

#ifndef _SPARKSEE_QUERY_CONTEXT_H_
#define _SPARKSEE_QUERY_CONTEXT_H_

/**
 * \addtogroup gdb
 * @{
 *
 * \file QueryContext.h
 * \brief It contains the definition of QueryContext class.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */

#include "gdb/common.h"

BEGIN_SPARKSEE_GDB_NAMESPACE

/*
 * Forward declaration of sparksee classes.
 */
class Query;
class QueryContextCore;

/**
 * \brief Query context interface.
 *
 * A QueryContext contains and manages the resources required to
 * run a Query. A Session is one example of a QueryContext
 * connected to a Sparksee database. The applications can implement
 * their own contexts to run queries out of Sparksee.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT QueryContext
{
public:
    /**
     * \brief Default constructor.
     */
    QueryContext();
    
    /**
     * \brief Destructor.
     */
    virtual ~QueryContext();
    
    /**
     * \brief Creates a new Query.
     */
    Query * NewQuery();

private:
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    QueryContext(const QueryContext & context);
    
    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    QueryContext & operator =(const QueryContext & context);
    
    /**
     * Interface to the core
     */
    QueryContextCore * core_context;
};

END_SPARKSEE_GDB_NAMESPACE

/** @} */
#endif // _SPARKSEE_QUERY_CONTEXT_H_
