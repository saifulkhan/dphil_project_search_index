/*
 * SPARKSEE: a library for out-of-core graph-based data storage and query processing.
 *
 * See the file LICENSE.txt for redistribution information.
 *
 * Copyright (c) 2005-2010 Sparsity Technologies, Barcelona (Spain)
 */

#ifndef _SPARKSEE_COMMUNITYDETECTION_H_
#define _SPARKSEE_COMMUNITYDETECTION_H_

/**
 * \addtogroup algorithms
 * @{
 *
 * \file CommunityDetection.h
 * \brief It contains the definition of CommunityDetection class.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */

#include "gdb/Graph.h"
#include "gdb/Session.h"
#include "gdb/Objects.h"

#include <map>
#include <vector>


BEGIN_SPARKSEE_ALGORITHMS_NAMESPACE


/**
 * \brief CommunityDetection class.
 * 
 * Any class implementing this abstract class can be used to solve
 * a problem related to graph connectivity as finding the strongly connected
 * components, finding the weakly connected components.
 *
 * Check out the 'Algorithms' section in the SPARKSEE User Manual for more
 * details on this.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT CommunityDetection
{
public:

    /**
     * \brief Destructor.
     */
    virtual ~CommunityDetection();

    /**
     * \brief Allows connectivity through nodes of the given type.
     */
    virtual void AddNodeType(sparksee::gdb::type_t type);

    /**
     * \brief Allows connectivity through all node types of the graph.
     */
    virtual void AddAllNodeTypes();

    /**
     * \brief Set which nodes can't be used.
     * This will replace any previously specified set of excluded nodes.
     * Should only be used to exclude the usage of specific nodes
     * from allowed node types because it's less efficient than
     * not allowing a node type.
     * \param nodes [in] A set of node identifiers that must be kept intact
     * until the destruction of the class.
     */
    virtual void ExcludeNodes(sparksee::gdb::Objects &nodes);

    /**
     * \brief Set which edges can't be used.
     * This will replace any previously specified set of excluded edges.
     * Should only be used to exclude the usage of specific edges
     * from allowed edge types because it's less efficient than
     * not allowing an edge type.
     * \param edges [in] A set of edge identifiers that must be kept intact
     * until the destruction of the class.
     */
    virtual void ExcludeEdges(sparksee::gdb::Objects &edges);


    /** Runs the algorithm in order to find the connected components.
     * <p>
     * This method can be called only once.
     */
    virtual void Run() = 0;


protected:

    /**
     * Creates a new instance of {@link CommunityDetection}.
     *
     * \param s [in] Session to get the graph from and calculate the communities
     */
    CommunityDetection(sparksee::gdb::Session &s);

    /**
     * \brief Allows connectivity through edges of the given type.
     * \param t [in] Edge type.
     * \param d [in] Edge direction.
     */
    void AddEdgeType(sparksee::gdb::type_t type, sparksee::gdb::EdgesDirection direction);

    /**
     * \brief Allows connectivity through all edge types of the graph.
     * \param d [in] Edge direction.
     */
    void AddAllEdgeTypes(sparksee::gdb::EdgesDirection direction);

    /**
     * \brief Session.
     */
    sparksee::gdb::Session * sess;
    /**
     * \brief Graph.
     */
    sparksee::gdb::Graph * graph;

    /**
     * \brief A type definition to store allowed edge types.
     */
    typedef std::map<sparksee::gdb::type_t, sparksee::gdb::EdgesDirection> EdgeTypes_t;
    /**
     * \brief Allowed edge types.
     */
    EdgeTypes_t edgeTypes;
    /**
     * \brief A type definition to store allowed node types.
     */
    typedef std::vector<sparksee::gdb::type_t> NodeTypes_t;
    /**
     * \brief Allowed node types.
     */
    std::vector<sparksee::gdb::type_t> nodeTypes;

    /**
     * \brief Identifiers of the nodes not visited.
     */
    sparksee::gdb::Objects *nodesNotVisited;
    /**
     * \brief True if the connectivity has been calculated.
     */
    sparksee::gdb::bool_t computed;
    /**
     * \brief The set of excluded nodes.
     */
    sparksee::gdb::Objects *excludedNodes;
    /**
     * \brief The set of excluded edges.
     */
    sparksee::gdb::Objects *excludedEdges;


    // -----------------------------------------------

    /**
     * Check that edges had been added.
     */
    void AssertAddedEdges();
    /**
     * Check that nodes had been added.
     */
    void AssertAddedNodes();
    /**
     * Check that the connectivity had not been calculated yet.
     */
    void AssertNotComputed();

    /**
     * Set all the selected nodes in nodesNotVisited.
     * That's all the nodes of the allowed node types but not the excluded ones.
     */
    void SetNodesNotVisited();

    /**
     * Check that the communities had been calculated.
     */
    void AssertComputed();
    /**
     * Check that the given edge type is valid
     */
    void AssertEdgeType(sparksee::gdb::type_t edgetype);
    /**
     * Check that the given node type is valid
     */
    void AssertNodeType(sparksee::gdb::type_t nodetype);

    /**
     * Check if the given node has an allowed type.
     */
    sparksee::gdb::bool_t IsNodeTypeAllowed(sparksee::gdb::oid_t nodeId);
    /**
     * Check if the given node is forbidden.
     */
    sparksee::gdb::bool_t IsNodeExcluded(sparksee::gdb::oid_t node);
    /**
     * Check if the given edge is forbidden.
     */
    sparksee::gdb::bool_t IsEdgeExcluded(sparksee::gdb::oid_t edge);

private:

    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    CommunityDetection(const CommunityDetection & conn);
    /**
     * \brief Non implemented to avoid use of empty constructor.
     */
    CommunityDetection();
};


END_SPARKSEE_ALGORITHMS_NAMESPACE

/** @} */
#endif // _SPARKSEE_COMMUNITYDETECTION_H_
