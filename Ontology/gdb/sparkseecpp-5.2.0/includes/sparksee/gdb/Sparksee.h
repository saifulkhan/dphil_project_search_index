/*
 * SPARKSEE: a library for out-of-core graph-based data storage and query processing.
 *
 * See the file LICENSE.txt for redistribution information.
 *
 * Copyright (c) 2005-2010 Sparsity Technologies, Barcelona (Spain)
 */

#ifndef _SPARKSEE_SPARKSEE_H_
#define _SPARKSEE_SPARKSEE_H_

/**
 * \addtogroup gdb
 * @{
 *
 * \file Sparksee.h
 * \brief It contains the declaration of Sparksee and SparkseeConfig classes.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */

#include "gdb/Handler.h"
#include <vector>

/*
 * Forward declaration of sparksee_core classes.
 */
namespace sparksee_core
{
    class Properties;
    class SPARKSEE;
    class LogConsumer;
}

BEGIN_SPARKSEE_GDB_NAMESPACE

/*
 * Forward declaration of sparksee classes.
 */
class Sparksee;
class Database;


/**
 * \brief Sparksee properties file.
 *
 * This class is implemented as a singleton, so all public methods are
 * static.
 *
 * It allows for getting the property values stored in a properties file. 
 * A properties file is a file where there is one line per property.
 * A property is defined by a key and a value as follows: key=value
 *
 * By default, this loads properties from the file './sparksee.cfg'.
 * The user may choose to load a different file by calling the method Load().
 *
 * If the default properties file or the one loaded by the user 
 * do not exist, then this behaves as loading an empty properties file.
 */
class SPARKSEE_EXPORT SparkseeProperties
{
private:

    /**
     * \brief Non implemented to avoid use of empty constructor.
     */
    SparkseeProperties();
    
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    SparkseeProperties(const SparkseeProperties &props);
    
    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    SparkseeProperties & operator =(const SparkseeProperties &props);
    
    /**
     * \brief Loaded properties instance.
     */
    static sparksee_core::Properties * props;
    
    /**
     * \brief Default properties file to load in case none is given by the user.
     */
    static const std::wstring DefaultPropertiesFile;
    
    /**
     * \brief Auxiliary string to return string properties.
     *
     * IMPORTANT: This may be a race condition in a concurrent scenario. 
     * But SparkseeProperties should never be used in a concurrent scenario.
     */
    static std::wstring aux;

public:
    
    /**
     * \brief Loads properties from the given file path.
     * \param path [in] File path to load properties from.
     */
    static void Load(const std::wstring & path);
    
    /**
     * Gets a property.
     * \param key [in] The name of the property to lookup.
     * \param def [in] Default value to be returned in case there is no
     * property with the name key.
     * \return The value of the property, or def if the key is not found.
     */
    static const std::wstring & Get(const std::wstring & key, const std::wstring & def);
    
    /**
     * Gets a property as an integer.
     * \param key [in] The name of the property to lookup.
     * \param def [in] Default value to be returned in case there is no
     * property with the name key.
     * \return The property value, or def if the key is not found or in 
     * case of error.
     */
    static int32_t GetInteger(const std::wstring & key, int32_t def);

    /**
     * Gets a property as a boolean.
     * \param key [in] The name of the property to lookup.
     * \param def [in] Default value to be returned in case there is no
     * property with the name key.
     * \return The property value, or def if the key is not found or in 
     * case of error.
     */
    static bool_t GetBoolean(const std::wstring & key, bool_t def);
    
    /**
     * Gets a property as a time unit.
     * 
     * A time unit is a string representation of a time duration with a time
     * unit such as '10s' or '3H'.
     *
     * Valid format for the string representation: Blanks at the begining or
     * at the end are ignored. No blanks are allowed between the time duration
     * and the unit time. 
     *
     * Allowed time units: 'D' for days, 'H' for hours, 'M' for minutes,
     * 'S' o 's' for seconds, 'm' for milliseconds and 'u' for microseconds.
     *
     * There is a special case: If no time unit is given, seconds is the default.
     * So, '10' means 10 seconds.
     *
     * \param key [in] The name of the property to lookup.
     * \param def [in] The default value (in microseconds) to be returned 
     * in case there is no property with the name key.
     * \return The time duration in microseconds, or def if the key is not found 
     * or in case of error.
     */
    static int64_t GetTimeUnit(const std::wstring & key, int64_t def);
};


/**
 * \brief Sparksee configuration class.
 *
 * If not specified, 0 means unlimited which is the maximum available.
 * For the pools that's the total cache size.
 * For the cache unlimited means nearly all the physical memory of the computer.
 * 
 * For each field, there is a default value. This value can be overrided
 * with values from a properties file (see SparkseeProperties class). Also, 
 * this settings can be overrided calling a specific setter.
 *
 * For each field, it is shown its default value and the property to override
 * this value:
 *
 * Extent size: 4KB ('sparksee.storage.extentsize' at SparkseeProperties).
 * 
 * Pages per extent: 1 page ('sparksee.storage.extentpages' at SparkseeProperties).
 * 
 * Pool frame size: 1 extent ('sparksee.io.pool.frame.size' at SparkseeProperties).
 *
 * Minimum size for the persistent pool: 64 frames ('sparksee.io.pool.persistent.minsize' at SparkseeProperties).
 *
 * Maximum size for the persistent pool: 0 frames ('sparksee.io.pool.persistent.maxsize' at SparkseeProperties).
 *
 * Minimum size for the temporary pool: 16 frames ('sparksee.io.pool.temporal.minsize' at SparkseeProperties).
 *
 * Maximum size for the temporary pool: 0 frames ('sparksee.io.pool.temporal.maxsize' at SparkseeProperties).
 *
 * Number of pools in the pool cluster: 0 pools ('sparksee.io.pool.clustersize' at SparkseeProperties). 0 or 1 means the clustering is disabled.
 *
 * Maximum size for the cache (all pools): 0 MB ('sparksee.io.cache.maxsize' at SparkseeProperties).
 *
 * License code: "" ('sparksee.license' at SparkseeProperties). No license code means evaluation license.
 *
 * Log level: Info ('sparksee.log.level' at SparkseeProperties).
 *
 * Log file: "sparksee.log" ('sparksee.log.file' at SparkseeProperties).
 *
 * Cache statistics: false (disabled) ('sparksee.cache.statistics' at SparkseeProperties).
 *
 * Cache statistics log file: "statistics.log" ('sparksee.cache.statisticsFile' at SparkseeProperties).
 *
 * Cache statistics snapshot time: 1000 msecs [TimeUnit] ('sparksee.cache.statisticsSnapshotTime' at SparkseeProperties).
 * 
 * Recovery enabled: false ('sparksee.io.recovery' at SparkseeProperties).
 * 
 * Recovery log file: "" ('sparksee.io.recovery.logfile' at SparkseeProperties).
 * 
 * Recovery cache max size: 1MB ('sparksee.io.recovery.cachesize' at SparkseeProperties).
 * 
 * Recovery checkpoint time: 60 seconds [TimeUnit] ('sparksee.io.recovery.checkpointTime' at SparkseeProperties).
 *
 * High-availability: false (disabled) ('sparksee.ha' at SparkseeProperties).
 *
 * High-availability coordinators: "" ('sparksee.ha.coordinators' at SparkseeProperties).
 *
 * High-availability IP: "" ('sparksee.ha.ip' at SparkseeProperties).
 *
 * High-availability sync polling: 0 (disabled) [TimeUnit] ('sparksee.ha.sync' at SparkseeProperties).
 *
 * High-availability master history: 1D (1 day) [TimeUnit] ('sparksee.ha.master.history' at SparkseeProperties).
 *
 * Use of TimeUnit:
 *
 * Those variables using TimeUnit allow for:
 *
 * <X>[D|H|M|S|s|m|u] 
 *
 * where <X> is a number followed by an optional character which represents 
 * the unit: D for days, H for hours, M for minutes, S or s for seconds, 
 * m for milliseconds and u for microseconds. If no unit character is given, 
 * seconds are assumed.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT SparkseeConfig
{
private:
    /**
     * \brief Size of the storage extent (in KB).
     */
    int32_t extentSize;
    
    /**
     * \brief Number of pages per extent.
     */
    int32_t extentPages;
    
    /**
     * \brief Size of a pool frame in number of extents.
     */
    int32_t poolFrameSize;
    
    /**
     * \brief Minimum size for the persistent pool in number of frames.
     */
    int32_t poolPersistentMinSize;
    
    /**
     * \brief Maximum size for the persistent pool in number of frames.
     */
    int32_t poolPersistentMaxSize;
    
    /**
     * \brief Minimum size for the temporary pool in number of frames.
     */
    int32_t poolTemporaryMinSize;
    
    /**
     * \brief Maximum size for the temporary pool in number of frames.
     */
    int32_t poolTemporaryMaxSize;

    /**
     * \brief Number of pools in each PoolCluster.
     */
    int32_t poolClusterSize;
    
    /**
     * \brief Maximum size for the cache (all pools) in MB.
     */
    int32_t cacheMaxSize;
    
    /**
     * \brief License code.
     */
    std::wstring license;
    
    /**
     * \brief Log file.
     */
    std::wstring logFile;
    
    /**
     * \brief LogLevel.
     */
    LogLevel logLevel;
    
    /**
     * \brief Cache statistics enabled or not.
     */
    bool_t cacheStats;
    
    /**
     * \brief Cache statistics log file.
     *
     * Useless if cache statistics are disabled.
     */
    std::wstring cacheStatsFile;
    
    /**
     * \brief Cache statistics snapshot time in microseconds.
     *
     * Useless if cache statistics are disabled.
     */
    int64_t cacheStatsSnapshotTime;    
    
    /**
     * \brief Rollback enabled or not.
     */
    bool_t rollbackEnabled;

    /**
     * \brief Recovery enabled or not.
     */
    bool_t recoveryEnabled;
    
    /**
     * \brief Recovery log file.
     */
    std::wstring recoveryLogFile;
    
    /**
     * \brief Maximum size for the recovery log cache in extents.
     */
    int32_t recoveryCacheMaxSize;
    
    /**
     * \brief Delay time (in microseconds) between automatic checkpoints.
     */
    int64_t recoveryCheckpointTime;
    
    /**
     * \brief High Availability mode enabled or not
     */
    bool_t haEnabled;

    /**
     * \brief The ip:port of this instance
     *
     * Useless if high availability mode is disabled
     */
    std::wstring haIP;

    /**
     * \brief The ip:port of the coordinators
     *
     * Useless if high availability mode is disabled
     */
    std::wstring haCoordinators;

    /**
     * \brief Slave polling interval time in microseconds
     *
     * Useless if distributed mode is disabled
     *
     * 0 means no polling.
     */
    int64_t haSync;

    /**
     * \brief The time interval the operations remains in the master for other slaves to synchronize in microseconds.
     *
     * Useless if distributed mode is disabled
     */
    int64_t haHistory;

    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    SparkseeConfig(const SparkseeConfig &cfg);
    
    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    SparkseeConfig & operator =(const SparkseeConfig &cfg);
    
public:
    
    /**
     * \brief Creates a new instance.
     *
     * Values are set with default values.
     */
    SparkseeConfig();
    
    /**
     * \brief Destructor.
     */
    virtual ~SparkseeConfig();

    /**
     * \brief Gets the size of a extent.
     * \return The size of a extent in KB.
     */
    int32_t GetExtentSize() const
    {
        return extentSize;
    }
    
    /**
     * \brief Sets the size of the extents in KB.
     * \param kBytes [in] The size of an extent in KB.
     * An extent can have a size between 4KB and 64KB, and it must be a power of 2.
     */
    void SetExtentSize(int32_t kBytes)
    {
        if ((kBytes != 4) && (kBytes != 8) && (kBytes != 16) && (kBytes != 32) && (kBytes != 64))
            throw WrongArgumentError("The extent size must be a power of 2 between 4KB and 64KB.");
        extentSize = kBytes;
    }
    
    /**
     * \brief Gets the number of pages per extent.
     * \return The number of pages per extent.
     */
    int32_t GetExtentPages() const
    {
        return extentPages;
    }
    
    /**
     * \brief Sets the number of pages per extent.
     * \param pages [in] The number of pages.
     * It must be at least 1 page and the page size must be greater than or equal to 4KB.
     */
    void SetExtentPages(int32_t pages)
    {
        if (pages < 1)
            throw WrongArgumentError("The number of pages must be at least 1 per extent.");
        if (pages > extentSize/4)
            throw WrongArgumentError("Too many pages per extent. The page size must be greater than or equal to 4KB.");
        extentPages = pages;
    }
    
    /**
     * \brief Gets the size of a pool frame in number of extents.
     * \return The size of a pool frame in number of extents.
     */
    int32_t GetPoolFrameSize() const
    {
        return poolFrameSize;
    }
    
    /**
     * \brief Sets the size of a pool frame in number of extents.
     * \param extents [in] The size of a pool frame in number of extents.
     * It must be non-negative.
     */
    void SetPoolFrameSize(int32_t extents)
    {
        if (0 > extents) throw WrongArgumentError("Expected a non-negative value");
        poolFrameSize = extents;
    }
    
    /**
     * \brief Gets the minimum size for the persistent pool in number of frames.
     * \return The minimum size for the persistent pool in number of frames.
     */
    int32_t GetPoolPersistentMinSize() const
    {
        return poolPersistentMinSize;
    }
    
    /**
     * \brief Sets the minimum size for the persistent pool in number of frames.
     * \param frames [in] The minimum size for the persistent pool in number of frames.
     * It must be non-negative.
     */
    void SetPoolPersistentMinSize(int32_t frames)
    {
        if (0 > frames) throw WrongArgumentError("Expected a non-negative value");
        poolPersistentMinSize = frames;
    }
    
    /**
     * \brief Gets the maximum size for the persistent pool in number of frames.
     * \return The maximum size for the persistent pool in number of frames.
     */
    int32_t GetPoolPersistentMaxSize() const
    {
        return poolPersistentMaxSize;
    }
    
    /**
     * \brief Sets the maximum size for the persistent pool in number of frames.
     * \param frames [in] The maximum size for the persistent pool in number of frames.
     * It must be non-negative.
     */
    void SetPoolPersistentMaxSize(int32_t frames)
    {
        if (0 > frames) throw WrongArgumentError("Expected a non-negative value");
        poolPersistentMaxSize = frames;
    }
    
    /**
     * \brief Gets the minimum size for the temporary pool in number of frames.
     * \return The minimum size for the temporary pool in number of frames.
     */
    int32_t GetPoolTemporaryMinSize() const
    {
        return poolTemporaryMinSize;
    }
    
    /**
     * \brief Sets the minimum size for the temporary pool in number of frames.
     * \param frames [in] The minimum size for the temporary pool in number of frames.
     * It must be non-negative.
     */
    void SetPoolTemporaryMinSize(int32_t frames)
    {
        if (0 > frames) throw WrongArgumentError("Expected a non-negative value");
        poolTemporaryMinSize = frames;
    }
    
    /**
     * \brief Gets the maximum size for the temporary pool in number of frames.
     * \return The maximum size for the temporary pool in number of frames.
     */
    int32_t GetPoolTemporaryMaxSize() const
    {
        return poolTemporaryMaxSize;
    }
    
    /**
     * \brief Sets the maximum size for the temporary pool in number of frames.
     * \param frames [in] The maximum size for the temporary pool in number of frames.
     * It must be non-negative.
     */
    void SetPoolTemporaryMaxSize(int32_t frames)
    {
        if (0 > frames) throw WrongArgumentError("Expected a non-negative value");
        poolTemporaryMaxSize = frames;
    }

    /**
     * \brief Gets the number of pools in each PoolCluster.
     * \return The number of pools in each PoolCluster.
     */
    int32_t GetPoolClusterSize() const
    {
        return poolClusterSize;
    }

    /**
     * \brief Sets the number of pools in each PoolCluster.
     * \param pools [in] The number of pools in each PoolCluster.
     * It must be non-negative.
     */
    void SetPoolClusterSize(int32_t pools)
    {
        if (0 > pools) throw WrongArgumentError("Expected a non-negative value");
        poolClusterSize = pools;
    }
    
    /**
     * \brief Gets the maximum size for the cache (all pools) in MB.
     * \return The maximum size for the cache (all pools) in MB.
     */
    int32_t GetCacheMaxSize() const
    {
        return cacheMaxSize;
    }
    
    /**
     * \brief Sets the maximum size for the cache (all pools) in MB.
     * \param megaBytes [in] The maximum size for the cache (all pools) in MB.
     * It must be non-negative.
     */
    void SetCacheMaxSize(int32_t megaBytes)
    {
        if (0 > megaBytes) throw WrongArgumentError("Expected a non-negative value");
        cacheMaxSize = megaBytes;
    }
    
    /**
     * \brief Gets the license code.
     * \return The license code.
     */
    const std::wstring & GetLicense() const
    {
        return license;
    }
    
    /**
     * \brief Sets the license code.
     * \param key [in] The license code.
     */
    void SetLicense(const std::wstring &key);
    
    /**
     * \brief Gets the log file.
     * \return The log file.
     */
    const std::wstring & GetLogFile() const
    {
        return logFile;
    }
    
    /**
     * \brief Sets the log file.
     * \param filePath [in] The log file.
     */
    void SetLogFile(const std::wstring & filePath)
    {
        logFile = filePath;
    }
    
    /**
     * \brief Gets the log level.
     * \return The LogLevel.
     */
    LogLevel GetLogLevel() const
    {
        return logLevel;
    }
    
    /**
     * \brief Sets the log level.
     * \param level [in] The LogLevel.
     */
    void SetLogLevel(LogLevel level)
    {
        logLevel = level;
    }
    
    /**
     * \brief Gets whether cache statistics are enabled or disabled.
     * \return TRUE if cache statistics are enabled, FALSE otherwise.
     */
    bool_t GetCacheStatisticsEnabled() const
    {
        return cacheStats;
    }
    
    /**
     * \brief Enables or disables cache statistics.
     * \param status [in] If TRUE this enables cache statistics, if FALSE this
     * disables cache statistics.
     */
    void SetCacheStatisticsEnabled(bool_t status)
    {
        cacheStats = status;
    }
    
    /**
     * \brief Gets the cache statistics log file.
     *
     * Useless if cache statistics are disabled.
     * \return The cache statistics log file.
     */
    const std::wstring & GetCacheStatisticsFile() const
    {
        return cacheStatsFile;
    }
    
    /**
     * \brief Sets the cache statistics log file.
     *
     * Useless if cache statistics are disabled.
     * \param filePath [in] The cache statistics log file.
     */
    void SetCacheStatisticsFile(const std::wstring & filePath)
    {
        cacheStatsFile = filePath;
    }
    
    /**
     * \brief Gets the cache statistics snapshot time in microseconds.
     * 
     * Useless if cache statistics are disabled.
     * \return The cache statistics snapshot time in microseconds.
     */
    int64_t GetCacheStatisticsSnapshotTime() const
    {
        return cacheStatsSnapshotTime;
    }
    
    /**
     * \brief Sets the cache statistics snapshot time.
     *
     * Useless if cache statistics are disabled.
     * \param microSeconds [in] The cache statistics snapshot time in microseconds.
     */
    void SetCacheStatisticsSnapshotTime(int64_t microSeconds)
    {
        if (0 > microSeconds) throw WrongArgumentError("Expected a positive value");
        cacheStatsSnapshotTime = microSeconds;
    }

    /**
     * \brief Gets whether the rollback is enabled or disabled.
     * \return TRUE if the rollback is enabled, FALSE otherwise.
     */
    bool_t GetRollbackEnabled() const
    {
        return rollbackEnabled;
    }

    /**
     * \brief Enables or disables the rollback.
     * \param status [in] If TRUE this enables the rollback, if FALSE then
     * disables it.
     */
    void SetRollbackEnabled(bool_t status)
    {
        rollbackEnabled = status;
    }

    /**
     * \brief Gets whether the recovery is enabled or disabled.
     * \return TRUE if the recovery is enabled, FALSE otherwise.
     */
    bool_t GetRecoveryEnabled() const
    {
        return recoveryEnabled;
    }
    
    /**
     * \brief Enables or disables the recovery.
     * \param status [in] If TRUE this enables the recovery, if FALSE then
     * disables it.
     */
    void SetRecoveryEnabled(bool_t status)
    {
        recoveryEnabled = status;
    }
    
    /**
     * \brief Gets the recovery log file.
     * \return The recovery log file.
     */
    const std::wstring & GetRecoveryLogFile() const
    {
        return recoveryLogFile;
    }
    
    /**
     * \brief Sets the recovery log file.
     * \param filePath [in] The recovery log file.
     * Left it empty for the default log file (same as <database_file_name>.log)
     */
    void SetRecoveryLogFile(const std::wstring & filePath)
    {
        recoveryLogFile = filePath;
    }
    
    /**
     * \brief Gets the maximum size for the recovery log cache in extents.
     * \return The maximum size for the recovery log cache in extents.
     */
    int32_t GetRecoveryCacheMaxSize() const
    {
        return recoveryCacheMaxSize;
    }
    
    /**
     * \brief Sets the maximum size for the recovery log cache in extents.
     * \param extents [in] The maximum size for the recovery log cache in extents.
     * A 0 sets the default value (extents up to 1MB).
     */
    void SetRecoveryCacheMaxSize(int32_t extents)
    {
        if (0 > extents) throw WrongArgumentError("Expected a non-negative value");
        recoveryCacheMaxSize = extents;
    }
    
    /**
     * \brief Gets the delay time (in microseconds) between automatic checkpoints.
     * \return The delay time (in microseconds) between automatic checkpoints.
     */
    int64_t GetRecoveryCheckpointTime() const
    {
        return recoveryCheckpointTime;
    }
    
    /**
     * \brief Sets the delay time (in microseconds) between automatic checkpoints.
     * \param microSeconds [in] The delay time (in microseconds) between automatic checkpoints.
     * A 0 forces a checkpoint after each commited transaction.
     */
    void SetRecoveryCheckpointTime(int64_t microSeconds)
    {
        if (0 > microSeconds) throw WrongArgumentError("Expected a non-negative value");
        recoveryCheckpointTime = microSeconds;
    }

    /**
     * \brief Gets whether high availability mode is enabled or disabled.
     * \return TRUE if high availability mode is enabled, FALSE otherwise.
     */
    bool_t GetHighAvailabilityEnabled() const
    {
        return haEnabled;
    }

    /**
     * \brief Enables or disables high availability mode.
     * \param status [in] If TRUE this enables high availability mode, if FALSE this
     * disables high availability mode.
     */
    void SetHighAvailabilityEnabled(bool_t status)
    {
        haEnabled = status;
    }

    /**
     * \brief Gets the IP address and port of the instance.
     * \return The IP address and port of the instance.
     */
    const std::wstring & GetHighAvailabilityIP() const
    {
        return haIP;
    }

    /**
     * \brief Sets the IP address and port of the instance.
     * \param ip [in] The IP address and port of the instance.
     */
    void SetHighAvailabilityIP(const std::wstring &ip)
    {
        haIP = ip;
    }

    /**
     * \brief Gets the coordinators address and port list.
     * \return The coordinators address and port list.
     */
    const std::wstring & GetHighAvailabilityCoordinators() const
    {
        return haCoordinators;
    }

    /**
     * \brief Sets the coordinators address and port list.
     * \param ip [in] The coordinators address and port list.
     */
    void SetHighAvailabilityCoordinators(const std::wstring &ip)
    {
        haCoordinators = ip;
    }

    /**
     * \brief Gets the synchronization polling time.
     * \return The Synchronization polling time.
     */
    int64_t GetHighAvailabilitySynchronization() const
    {
        return haSync;
    }

    /**
     * \brief Sets the synchronization polling time.
     * \param microSeconds [in] The synchronization polling time.
     */
    void SetHighAvailabilitySynchronization(int64_t microSeconds)
    {
        haSync = microSeconds;
    }

    /**
     * \brief Gets the master's history log.
     * \return The master's history log.
     */
    int64_t GetHighAvailabilityMasterHistory() const
    {
        return haHistory;
    }

    /**
     * \brief Sets the master's history log.
     * \param filePath [in] The master's history log.
     */
    void SetHighAvailabilityMasterHistory(int64_t filePath)
    {
        haHistory = filePath;
    }

private:
    // Private Settings
    bool_t te;
    std::wstring tf;
    int32_t tl, tg, tfm, tm, tbf;
    friend class Sparksee;
};


/**
 * \brief Sparksee class.
 *
 * All Sparksee programs must have one single Sparksee instance to manage one
 * or more Database instances. 
 *
 * This class allows for the creation of new Databases or open an existing one.
 *
 * \author Sparsity Technologies http://www.sparsity-technologies.com
 */
class SPARKSEE_EXPORT Sparksee
: private Handler<sparksee_core::SPARKSEE>
{
public:
    
    /**
     * \brief Sparksee version.
     */
    static const std::wstring Version;
    
    /**
     * \brief Creates a new instance.
     * \param config [in] Sparksee configuration.
     */
    Sparksee(const SparkseeConfig & config);
    
    /**
     * \brief Destructor.
     */
    virtual ~Sparksee();
    
    /**
     * \brief Creates a new Database instance.
     * \param path [in] Database storage file.
     * \param alias [in] Database alias name.
     * \return A Database instance.
     * \exception FileNotFoundException If the given file cannot be created.
     */
    Database * Create(const std::wstring & path, const std::wstring & alias)
    throw(sparksee::gdb::FileNotFoundException, sparksee::gdb::Error);
    
    /**
     * \brief Opens an existing Database instance.
     * \param path [in] Database storage file.
     * \param readOnly [in] If TRUE, open Database in read-only mode.
     * \return A Database instance.
     * \exception FileNotFoundException If the given file does not exist.
     */
    Database * Open(const std::wstring & path, bool_t readOnly)
    throw(sparksee::gdb::FileNotFoundException, sparksee::gdb::Error);
    
    /**
     * \brief Restores a Database from a backup file. See the Graph class Backup method.
     * \param path [in] Database storage file.
     * \param backupFile [in] The Backup file to be restored.
     * \return A Database instance.
     * \exception FileNotFoundException If the given file cannot be created, or the exported data file does not exists.
     */
    Database * Restore(const std::wstring & path, const std::wstring & backupFile)
    throw(sparksee::gdb::FileNotFoundException, sparksee::gdb::Error);
    

private:
    
    /**
     * \brief Stores sparksee_core LogConsumer reference.
     *
     * For the moment, just one is used (the default one), but it is ready
     * for multiple LogConsumer references.
     */
    std::vector<sparksee_core::LogConsumer *> logConsumers;
    
    /**
     * \brief Non implemented to avoid use of copy constructor.
     */
    Sparksee(const Sparksee & d);
    
    /**
     * \brief Non implemented to avoid use of assignment operator.
     */
    Sparksee & operator =(const Sparksee & d);
};


END_SPARKSEE_GDB_NAMESPACE

/** @} */
#endif // _SPARKSEE_SPARKSEE_H_
