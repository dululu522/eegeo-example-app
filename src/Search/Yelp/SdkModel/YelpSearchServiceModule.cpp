// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchServiceModule.h"
#include "YelpSearchJsonParser.h"
#include "YelpBusinessJsonParser.h"
#include "YelpSearchService.h"
#include "YelpCategoryToTagMapper.h"
#include "YelpSearchConstants.h"
#include "YelpSearchQueryFactory.h"
#include "YelpBusinessQueryFactory.h"
#include "EegeoTagIconMapperFactory.h"
#include <vector>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            YelpSearchServiceModule::YelpSearchServiceModule(
                Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                Net::SdkModel::INetworkCapabilities& networkCapabilities,
                Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                const Search::SdkModel::SearchTags& searchTags,
				const std::string& yelpConsumerKey,
				const std::string& yelpConsumerSecret,
				const std::string& yelpOAuthToken,
				const std::string& yelpOAuthTokenSecret,
                Eegeo::Helpers::IFileIO& fileIO)
            : m_pSearchService(NULL)
            , m_pSearchQueryFactory(NULL)
            , m_pYelpBusinessQueryFactory(NULL)
            , m_pYelpSearchJsonParser(NULL)
            , m_pYelpBusinessJsonParser(NULL)
            , m_pYelpCategoryMapper(NULL)
            , m_pTagIconMapper(NULL)
            {
                m_pTagIconMapper = TagSearch::SdkModel::CreateTagIconMapper(searchTags);
                
                std::vector<std::string> appTags;
                appTags.reserve(searchTags.tags.size());
                for(const auto& i : searchTags.tags)
                {
                    appTags.push_back(i.tag);
                }
   
                const auto& yelpData = Yelp::SearchConstants::ParseYelpData(fileIO, appTags, "yelp_map.json");

                m_pYelpCategoryMapper = Eegeo_NEW(Yelp::SdkModel::YelpCategoryToTagMapper)(
                        webRequestFactory,
                        yelpData.yelpFoundationCategoryToAppTag,
                        yelpData.defaultAppTag);

                m_pYelpSearchJsonParser = Eegeo_NEW(Yelp::SdkModel::YelpSearchJsonParser)(*m_pYelpCategoryMapper, *m_pTagIconMapper);
                
                m_pYelpBusinessJsonParser = Eegeo_NEW(Yelp::SdkModel::YelpBusinessJsonParser)(*m_pYelpCategoryMapper, *m_pTagIconMapper);

                m_pSearchQueryFactory = Eegeo_NEW(Yelp::SdkModel::YelpSearchQueryFactory)(
                    yelpConsumerKey,
                    yelpConsumerSecret,
                    yelpOAuthToken,
                    yelpOAuthTokenSecret,
                    yelpData.appTagToYelpCategory,
                    webRequestFactory);
                
                m_pYelpBusinessQueryFactory = Eegeo_NEW(Yelp::SdkModel::YelpBusinessQueryFactory)(
                                                                                                  yelpConsumerKey,
                                                                                                  yelpConsumerSecret,
                                                                                                  yelpOAuthToken,
                                                                                                  yelpOAuthTokenSecret,
                                                                                                  *m_pYelpBusinessJsonParser,
                                                                                                  webRequestFactory);

                m_pSearchService = Eegeo_NEW(Yelp::SdkModel::YelpSearchService)(*m_pSearchQueryFactory,
                                                                                *m_pYelpBusinessQueryFactory,
                                                                                *m_pYelpSearchJsonParser,
                                                                                networkCapabilities,
                                                                                appTags);
            }

            YelpSearchServiceModule::~YelpSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pSearchQueryFactory;
                Eegeo_DELETE m_pYelpBusinessQueryFactory;
                Eegeo_DELETE m_pYelpSearchJsonParser;
                Eegeo_DELETE m_pYelpBusinessJsonParser;
                Eegeo_DELETE m_pYelpCategoryMapper;
                Eegeo_DELETE m_pTagIconMapper;
            }

            Search::SdkModel::ISearchService& YelpSearchServiceModule::GetSearchService() const
            {
                return *m_pSearchService;
            }
        }
    }
}