#!/bin/bash
#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at http://mozilla.org/MPL/2.0/.

(set -o igncr) 2>/dev/null && set -o igncr; # comment is needed

## Make sure McAfee is started
net start mcshield

