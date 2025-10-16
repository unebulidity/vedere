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
///   File: path.hpp
///
/// Author: $author$
///   Date: 6/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_EXPLORE_DIRECTORY_FS_PATH_HPP
#define _VEDERE_APP_GUI_EXPLORE_DIRECTORY_FS_PATH_HPP

#include "vedere/app/gui/explore/directory/path.hpp"

#include "xos/os/fs/directory/path.hpp"
#include "xos/os/fs/directory/entry.hpp"
#include "xos/os/fs/entry.hpp"

#define VEDERE_APP_GUI_EXPLORE_DIRECTORY_FS_PATH_SCHEME_CHARS "file"

namespace vedere {
namespace gui {
namespace app {
namespace explore {
namespace directory {
namespace fs {

typedef directory::path path_implements;
typedef base path_extends;
///////////////////////////////////////////////////////////////////////
///  Class: path
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS path: virtual public path_implements, public path_extends {
public:
    typedef path_implements Implements;
    typedef path_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    path(): root_(0) {
    }
    virtual ~path() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual directory::path* open(directory::path& root, const entry& parent) {
        if (root.get_root() == ((directory::path*)root_)) {
            xos::base::string name;
            const char* chars = 0;
            size_t length = 0;
            if ((chars = parent.path(length)) && (0 < length)) {
                name.append(chars, length);
                name.append(separator());
            }
            name.append(parent.name());
            if ((chars = name.chars(length)) && (0 < length)) {
                path* child = 0;
                if ((child = new path())) {
                    if ((child->open(chars))) {
                        child->root_ = root_;
                        return child;
                    }
                    delete child;
                }
            }
        }
        return 0;
    }
    virtual bool open(const char* name) {
        if ((this->closed())) {
            VEDERE_LOG_MESSAGE_DEBUG("open(\"" << name << "\")...");
            if ((path_.open(name))) {
                VEDERE_LOG_MESSAGE_DEBUG("...open(\"" << name << "\")");
                root_ = this;
                name_.assign(name);
                return true;
            }
        }
        return false;
    }
    virtual bool reopen() {
        path* root = root_;
        const char* chars = name_.has_chars();
        if ((root) && (chars)) {
            xos::base::string name(chars);
            if ((this->open(name.chars()))) {
                root_ = root;
                return true;
            }
        }
        return false;
    }
    virtual bool close() {
        root_ = 0;
        name_.clear();
        if ((path_.close())) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry* get_first_entry() {
        entry* e = 0;
        for (xos::os::fs::directory::entry* de = path_.get_first_entry();
             de; de = path_.get_next_entry()) {
            if ((e = on_entry(*de))) {
                break;
            }
        }
        return e;
    }
    virtual entry* get_next_entry() {
        entry* e = 0;
        for (xos::os::fs::directory::entry* de = path_.get_next_entry();
             de; de = path_.get_next_entry()) {
            if ((e = on_entry(*de))) {
                break;
            }
        }
        return e;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry* on_entry
    (const xos::os::fs::directory::entry& de) {
        entry* e = 0;
        xos::fs::entry_type t = de.type();
        switch(t & (xos::fs::entry_type_directory | xos::fs::entry_type_file)) {
        case xos::fs::entry_type_directory:
            if (!(de.is_circular())) {
                e = on_entry(de, entry_type_directory);
            }
            break;
        case xos::fs::entry_type_file:
            e = on_entry(de, entry_type_file);
            break;
        }
        return e;
    }
    virtual entry* on_entry
    (const xos::os::fs::directory::entry& de, entry_type t) {
        xos::fs::time_when_which dtimes = de.times();
        time_when_which times = time_when_none;
        entry_.set_type(t);
        entry_.set_name(de.name());
        entry_.set_path(name_.chars());
        entry_.set_size(de.size());
        for (xos::fs::time_when_which t = xos::fs::first_time_when; t < xos::fs::next_time_when; t <<= 1) {
            const xos::fs::time* tm = 0;
            if ((t & dtimes) && (tm = de.time_which(t))) {
                uint year = tm->year(), month = tm->month(), day = tm->day();
                switch(t) {
                case xos::fs::time_when_modified: {
                    time t(time_when_modified, year, month, day);
                    times |= time_when_modified;
                    entry_.set_time_modified(t);
                    break; }
                case xos::fs::time_when_accessed: {
                    time t(time_when_accessed, year, month, day);
                    times |= time_when_accessed;
                    entry_.set_time_accessed(t);
                    break; }
                case xos::fs::time_when_created: {
                    time t(time_when_created, year, month, day);
                    times |= time_when_created;
                    entry_.set_time_created(t);
                    break; }
                case xos::fs::time_when_changed: {
                    time t(time_when_changed, year, month, day);
                    times |= time_when_changed;
                    entry_.set_time_changed(t);
                    break; }
                }
            }
        }
        entry_.set_times(times);
        return &entry_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual directory::path* get_root() const {
        return root_;
    }
    virtual const char* name() const {
        return name_.chars();
    }
    virtual const char* scheme() const {
        return VEDERE_APP_GUI_EXPLORE_DIRECTORY_FS_PATH_SCHEME_CHARS;
    }
    virtual const char* separator() const {
        return XOS_FS_DIRECTORY_SEPARATOR_CHARS;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    path* root_;
    xos::base::string name_;
    xos::os::fs::directory::path path_;
    entry entry_;
};

} // namespace fs 
} // namespace directory 
} // namespace explore 
} // namespace app 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_EXPLORE_DIRECTORY_FS_PATH_HPP 
