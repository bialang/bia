#ifndef BIA_COMPILER_ELVE_HELPERS_HPP_
#define BIA_COMPILER_ELVE_HELPERS_HPP_

#include "present.hpp"

namespace bia {
namespace compiler {
namespace elve {

tokens_type statement(present present, tokens_type tokens);
tokens_type batch(present present, tokens_type tokens);
tokens_type declaration(present present, tokens_type tokens);
template<typename Destination>
tokens_type expression(present present, tokens_type tokens, Destination destination);
tokens_type expression(present present, tokens_type tokens, bytecode::member::push destination);
tokens_type for_each(present present, tokens_type tokens);
tokens_type if_(present present, tokens_type tokens);
tokens_type import(present present, tokens_type tokens);
template<typename Source, typename Destination>
tokens_type member_call(present present, tokens_type tokens, Source source, Destination destination);
template<typename Destination>
tokens_type member(present present, tokens_type tokens, Destination destination);
tokens_type parameter(present present, tokens_type tokens);
tokens_type statement(present present, tokens_type tokens);
tokens_type while_(present present, tokens_type tokens);
tokens_type function(present present, tokens_type tokens);
tokens_type return_(present present, tokens_type tokens);

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
