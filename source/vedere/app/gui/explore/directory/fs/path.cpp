///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: path.cpp
///
/// Author: $author$
///   Date: 6/29/2015
///////////////////////////////////////////////////////////////////////
#include "vedere/app/gui/explore/directory/fs/path.hpp"

namespace vedere {
namespace gui {
namespace app {
namespace explore {
namespace directory {
namespace fs {

///////////////////////////////////////////////////////////////////////
///  Class: default_path
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS default_path: public path {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    default_path(): the_default_(the_default()) {
        if (!(the_default() == this)) {
            the_default() = this;
        }
    }
    virtual ~default_path() {
        if ((the_default() == this)) {
            the_default() = the_default_;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual directory::path* get(const char* scheme) const {
        int unequal = 0;
        if (!(unequal = chars_t::compare(scheme, this->scheme()))) {
            return ((directory::path*)this);
        } else {
            if ((the_default_)) {
                return the_default_->get(scheme);
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    directory::path* the_default_;
} the_default;

} // namespace fs 
} // namespace directory 
} // namespace explore 
} // namespace app 
} // namespace gui 
} // namespace vedere 
