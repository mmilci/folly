/*
 * Copyright 2016 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOLLY_EXPERIMENTAL_EXCEPTION_TRACER_EXCEPTIONTRACERLIB_H_
#define FOLLY_EXPERIMENTAL_EXCEPTION_TRACER_EXCEPTIONTRACERLIB_H_

#include <typeinfo>
#include <exception>

namespace folly {
namespace exception_tracer {

namespace detail {
/*
 * Unfortunately due to ambiguous nature of exception specifiers,
 * standard does not allow them to appear in typedefs or alias-declarations.
 * We, however, want callbacks to be exception safe.
 * This dummies are an ugly workaround that problem.
 */
void dummyCxaThrow(void*, std::type_info*, void (*)(void*)) noexcept;
void dummyCxaBeginCatch(void*) noexcept;
void dummyCxaRethrow(void) noexcept;
void dummyCxaEndCatch(void) noexcept;
void dummyRethrowException(std::exception_ptr) noexcept;
}

using CxaThrowType = decltype(&detail::dummyCxaThrow);
using CxaBeginCatchType = decltype(&detail::dummyCxaBeginCatch);
using CxaRethrowType = decltype(&detail::dummyCxaRethrow);
using CxaEndCatchType = decltype(&detail::dummyCxaEndCatch);
using RethrowExceptionType = decltype(&detail::dummyRethrowException);

void registerCxaThrowCallback(CxaThrowType callback);
void registerCxaBeginCatchCallback(CxaBeginCatchType callback);
void registerCxaRethrowCallback(CxaRethrowType callback);
void registerCxaEndCatchCallback(CxaEndCatchType callback);
void registerRethrowExceptionCallback(RethrowExceptionType callback);
}
}

#endif /* FOLLY_EXPERIMENTAL_EXCEPTION_TRACER_EXCEPTIONTRACERLIB_H_ */
