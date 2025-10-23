// Copyright 2005-2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the 'License');
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an 'AS IS' BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// See www.openfst.org for extensive documentation on this weighted
// finite-state transducer library.
//
// Creates a finite-state archive from component FSTs.

#ifndef FST_EXTENSIONS_FAR_CREATE_H_
#define FST_EXTENSIONS_FAR_CREATE_H_

#ifndef _MSC_VER
#include <libgen.h>
#endif

#include <sstream>
#include <string>
#include <vector>

#include <fst/extensions/far/far.h>

namespace fst {

#ifdef _MSC_VER
inline char* far_create_internal_basename(char* path) {
    static char dot[] = ".";
    static char slash[] = "/";

    char* last_sep = nullptr;
    char* p;

    if (!path || *path == '\0') {
        return dot;
    }

    char* end = path + strlen(path) - 1;
    while (end > path && (*end == '/' || *end == '\\')) {
        *end = '\0';
        end--;
    }

    p = path;
    while (*p) {
        if (*p == '/' || *p == '\\') {
            last_sep = p;
        }
        p++;
    }

    if (last_sep == nullptr) {
        if (path[0] != '\0' && path[1] == ':' && path[2] == '\0') {
            return slash;
        }

        return path;
    }

    if (last_sep == path && *(last_sep + 1) == '\0') {
        return slash;
    }

    return last_sep + 1;
}
#endif

template <class Arc>
void FarCreate(const std::vector<std::string> &in_sources,
               const std::string &out_source, const int32 generate_keys,
               const FarType &far_type, const std::string &key_prefix,
               const std::string &key_suffix) {
  std::unique_ptr<FarWriter<Arc>> far_writer(
      FarWriter<Arc>::Create(out_source, far_type));
  if (!far_writer) return;
  for (size_t i = 0; i < in_sources.size(); ++i) {
    std::unique_ptr<Fst<Arc>> ifst(Fst<Arc>::Read(in_sources[i]));
    if (!ifst) return;
    std::string key;
    if (generate_keys > 0) {
      std::ostringstream keybuf;
      keybuf.width(generate_keys);
      keybuf.fill('0');
      keybuf << i + 1;
      key = keybuf.str();
    } else {
      auto *source = new char[in_sources[i].size() + 1];
      strcpy(source, in_sources[i].c_str());  // NOLINT
#ifdef _MSC_VER
      key = far_create_internal_basename(source);
#else
      key = basename(source);
#endif
      delete[] source;
    }
    far_writer->Add(key_prefix + key + key_suffix, *ifst);
  }
}

}  // namespace fst

#endif  // FST_EXTENSIONS_FAR_CREATE_H_
