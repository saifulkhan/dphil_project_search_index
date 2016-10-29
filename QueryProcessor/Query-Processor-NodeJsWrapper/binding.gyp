##
## Exception handling error https://github.com/TooTallNate/node-gyp/issues/17
##

{
  "targets": [
    {
      "target_name": 'QueryProcessorAddon',
      "sources": [ 'QueryProcessorAddon.cpp', 'QueryProcessorWrapper.cpp'],
      "cflags": ["-std=c++0x -Wall -W -fPIC"],
      "cflags!": [
                      '-fno-exceptions', '-ffunction-sections', '-fdata-sections'
                  ],
        'cflags_cc!': [ '-fno-exceptions' ],

      "OTHER_CPLUSPLUSFLAGS" : ['-std=c++11','-stdlib=libc++'],
      "OTHER_LDFLAGS": ['-stdlib=libc++'],
      'include_dirs': ['/home/search-engine/install/include/QueryProcessor',
                       '/home/search-engine/install/include/Common',
                       '/home/search-engine/install/include/LanguageProcessor',
                       '/home/search-engine/install/include/Index',
                       '/home/search-engine/install/include/Ontology',
                       '/home/search-engine/install/include/sparksee',
                       '/mnt/DATA/Dropbox/DPhil-Research/Dev/QueryProcessorWrapper/Test'],
      'link_settings': {
        'libraries': ['-L/home/search-engine/install/lib',
                      '-lQueryProcessor', '-lOntology', '-lLanguageProcessor', '-lCommon', '-ltinyxml', '-lIndex', '-lsparksee', '-ljson_spirit']
      }

    }
  ]
}

