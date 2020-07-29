#include <graphene/chain/protocol/nft_ops.hpp>
#include <graphene/chain/protocol/operations.hpp>

namespace graphene
{
namespace chain
{

bool is_valid_nft_token_name(const string &name)
{
   try
   {
      const size_t len = name.size();
      // NFT_TOKEN_MIN_LENGTH <= len minimum length check
      if (len < NFT_TOKEN_MIN_LENGTH)
      {
         return false;
      }
      // len <= NFT_TOKEN_MAX_LENGTH max length check
      if (len > NFT_TOKEN_MAX_LENGTH)
      {
         return false;
      }
      // First character should be a letter between a-z/A-Z
      if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')))
      {
         return false;
      }
      // Any character should either be a small case letter a-z or a digit 0-9
      for (const auto &ch : name)
      {
         if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == ' ')))
         {
            return false;
         }
      }

      return true;
   }
   FC_CAPTURE_AND_RETHROW((name))
}

void nft_metadata_create_operation::validate() const
{
   FC_ASSERT(fee.amount >= 0, "Fee must not be negative");
   FC_ASSERT(is_valid_nft_token_name(name), "Invalid NFT name provided");
   FC_ASSERT(is_valid_nft_token_name(symbol), "Invalid NFT symbol provided");
   FC_ASSERT(base_uri.length() <= NFT_URI_MAX_LENGTH, "Invalid NFT Base URI");
}

void nft_metadata_update_operation::validate() const
{
   FC_ASSERT(fee.amount >= 0, "Fee must not be negative");
   if(name)
      FC_ASSERT(is_valid_nft_token_name(*name), "Invalid NFT name provided");
   if(symbol)
      FC_ASSERT(is_valid_nft_token_name(*symbol), "Invalid NFT symbol provided");
   if(base_uri)
      FC_ASSERT((*base_uri).length() <= NFT_URI_MAX_LENGTH, "Invalid NFT Base URI");
}

void nft_mint_operation::validate() const
{
   FC_ASSERT(fee.amount >= 0, "Fee must not be negative");
   FC_ASSERT(token_uri.length() <= NFT_URI_MAX_LENGTH, "Invalid NFT Token URI");
}

} // namespace chain
} // namespace graphene
