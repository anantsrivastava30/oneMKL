/*******************************************************************************
* Copyright 2022 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions
* and limitations under the License.
*
*
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef _ONEMKL_DFT_DESCRIPTOR_HPP_
#define _ONEMKL_DFT_DESCRIPTOR_HPP_

#if __has_include(<sycl/sycl.hpp>)
#include <sycl/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

#include "oneapi/mkl/types.hpp"
#include "oneapi/mkl/detail/backend_selector.hpp"

#include "oneapi/mkl/dft/detail/descriptor_impl.hpp"
#include "oneapi/mkl/dft/detail/dft_loader.hpp"

namespace oneapi {
namespace mkl {
namespace dft {

template <precision prec, domain dom>
class descriptor {
private:
    sycl::queue queue_;
    std::unique_ptr<detail::descriptor_impl> pimpl_;
public:
    // Syntax for 1-dimensional DFT
    descriptor(std::int64_t length)
        : pimpl_(detail::create_descriptor<prec, dom>(length)) {}

    // Syntax for d-dimensional DFT
    descriptor(std::vector<std::int64_t> dimensions);

    // ~descriptor();

    void set_value(config_param param, ...);

    void get_value(config_param param, ...);

    void commit(sycl::queue& queue);

    sycl::queue& get_queue() {
        return queue_;
    };
};

} //namespace dft
} //namespace mkl
} //namespace oneapi


#endif // _ONEMKL_DFT_DESCRIPTOR_HPP_