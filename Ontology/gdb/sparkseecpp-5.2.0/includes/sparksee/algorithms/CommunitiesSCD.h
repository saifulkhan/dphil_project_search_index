/*
 * SPARKSEE: a library for out-of-core graph-based data storage and query processing.
 *
 * See the file LICENSE.txt for redistribution information.
 *
 * Copyright (c) 2005-2010 Sparsity Technologies, Barcelona (Spain)
 */

#ifndef _SPARKSEE_COMMUNITIESSCD_H_
#define _SPARKSEE_COMMUNITIESSCD_H_

/**
 * \addtogroup algorithms
 * @{
 *
 * \file CommunitiesSCD.h
 * \brief It contains the definition of CommunitiesSCD class.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */


#include "algorithms/DisjointCommunityDetection.h"


BEGIN_SPARKSEE_ALGORITHMS_NAMESPACE


/**
 * \brief CommunitiesSCD class.
 * 
 * Implementation of the community detection algorithm "Scalable Community Detection" based on the
 * paper "High quality, scalable and parallel community detection for large real graphs" by
 * Arnau Prat-Perez, David Dominguez-Sal, Josep-Lluis Larriba-Pey - WWW 2014.
 *
 * The purpose of this algorithm is to find disjoint communities in an <b> undirected </b> graph
 * or in a directed graph which will be considered as an undirected one.
 *
 * It is possible to set some restrictions after constructing a new instance
 * of this class and before running it in order to limit the results.
 *
 * After the execution, we can retrieve the results stored in an instance of the
 * DisjointCommunities class using the getCommunities method.
 *
 * Check out the 'Algorithms' section in the SPARKSEE User Manual for more
 * details on this.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT CommunitiesSCD : public DisjointCommunityDetection
{
public:

    /**
     * Creates a new instance of {@link CommunitiesSCD}.
     * After creating this instance is required to indicate the set of edge types
     * and the set of node types which will be navigated through while traversing
     * the graph in order to find the communities.
     * \param session [in] Session to get the graph from and calculate the communities
     */
    CommunitiesSCD(sparksee::gdb::Session &session);

    /**
     * \brief Destructor.
     */
    virtual ~CommunitiesSCD();

    /**
     * Sets the size of the lookahead iterations to look.
     *
     * @param lookahead [in] Number of iterations.
     * It must be positive or zero.
     */
    void SetLookAhead(sparksee::gdb::int32_t lookahead);
    
    /**
     * \brief Executes the algorithm.
     */
    void Run();

private:
    sparksee::gdb::int32_t m_lookahead;
    void KeepEquivalentEdges( sparksee::gdb::Objects &equivalentEdges, sparksee::gdb::oid_t tail, sparksee::gdb::oid_t head);

    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    CommunitiesSCD(const CommunitiesSCD & wc);
    /**
     * \brief Non implemented to avoid use of empty constructor.
     */
    CommunitiesSCD();
};


END_SPARKSEE_ALGORITHMS_NAMESPACE

/** @} */
#endif // _SPARKSEE_COMMUNITIESSCD_H_
