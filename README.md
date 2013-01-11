Unsupported Contributions Repository
====================================
The OpenFOAM Foundation hosts a public source code repository for users who
wish to share their code modifications of OpenFOAM with the wider community.
This repository code is **not part of the official OpenFOAM distribution** and
is known as the Unsupported Contributions Repository. The code is not endorsed
or supported by ESI-OpenCFD, the producers of OpenFOAM. However, code of
sufficient quality, usefulness and maturity may be migrated by ESI-OpenCFD into
the official OpenFOAM code base for distribution by the OpenFOAM Foundation.

The OpenFOAM Foundation distributes the official OpenFOAM code base via
[GitHub][] through a user account called *OpenFOAM*, as described in the
[Repository Release page][release page]. The Foundation creates a new
repository for each major release of OpenFOAM, with names such as
OpenFOAM-2.1.x.

[GitHub]: http://github.com
[release page]: http://www.openfoam.org/download/git.php

The **Unsupported Contributions Repository** resides on GitHub under the user
account [*Unsupported-Contrib-OpenFOAM*][user]. Like the official code, a
separate repository is created for each major release of OpenFOAM, *e.g.*
[`Unsupported-Contrib-OpenFOAM-2.1.x`][repo]. Each *new* repository will
contain the following set of directories, with no files:

<dl>
  <dt><code>src</code></dt>
    <dd>source code for libraries;</dd>
  <dt><code>applications</code></dt>
    <dd>source code for applications (solvers and utilities);</dd>
  <dt><code>tutorials</code></dt>
    <dd>example cases.</dd>
</dl>

[repo]: http://github.com/Unsupported-Contrib-OpenFOAM/Unsupported-Contrib-OpenFOAM-2.1.x
[user]: http://github.com/Unsupported-Contrib-OpenFOAM

Contributing OpenFOAM Code
--------------------------
The contribution process is managed through GitHub. A contributor first forks
the [`Unsupported-Contrib-OpenFOAM-2.1.x`][repo] repository, adds their own
code, then requests that their developments are merged back into the
unsupported repository. Each merge request will be assessed by the repository
administrators against the following criteria:

* Where possible, contributions should take the form of fully encapsulated
  libraries, applications and example cases; the contributed files should fit
  within the repository directory structure described above.
* Submitted code must follow the [coding style guidelines][] to ensure
  consistency with existing code.
* All new source files must begin with a banner including a copyright statement
  with the relevant year and author name(s) inserted, see [example banner][].
* All modified source files must retain the original copyright statement, and
  include a notice stating the modification(s), including author name and date,
  see [example notices][].
* All files must be distributed under the [General Public License (GPL) version
  3][gpl3], and therefore must include an appropriate license notice, see
  [example license notice][].
* The Foundation will not accept any OpenFOAM code that is known to have been
  distributed elsewhere in a manner that violates the terms of the GPL.
* The Foundation will not accept code from any person known to have distributed
  any OpenFOAM code in a manner that violates the terms of the GPL.

[coding style guidelines]: http://www.openfoam.org/contrib/code-style.php
[example banner]: http://www.openfoam.org/contrib/unsupported-examples.php#new-source-banner
[example notices]: http://www.openfoam.org/contrib/unsupported-examples.php#modified-source-banner
[gpl3]: http://www.gnu.org/licenses/gpl.html
[example license notice]: http://www.openfoam.org/contrib/unsupported-examples.php#license-notice

How to Contribute
-----------------
Please follow the steps below to contribute to the
[`Unsupported-Contrib-OpenFOAM-2.1.x`][repo] repository:

1.  Create a **public**, personal account on GitHub (unless you have one
    already), by going to https://github.com and selecting *Sign up for Free*.
2.  Log into your account, and go to the [*Unsupported-Contrib-OpenFOAM user
    account*][user].
3.  From the *Repositories* tab, select the repository version (*e.g.* 2.1.x)
    to which you wish to contribute.
4.  Click the *Fork* button to create a forked repository in your own user
    account.
5.  Clone your forked repository onto your local machine, *e.g.* by the
    following command (for the account *contributor* and repository
    [`Unsupported-Contrib-OpenFOAM-2.1.x`][repo]:


    ```
    git clone git@github.com:contributor/Unsupported-Contrib-OpenFOAM-2.1.x.git
    ```

6. Modify your forked repository locally.
7. Push your changes to your repository on GitHub. Note that this will place
   your code in **the public domain** so any pushed files should conform to the
   GPL as described in [*Contributing OpenFOAM Code*][] (above).
8. To submit a contribution to the [`Unsupported-Contrib-OpenFOAM`][repo]
   repository, issue a *Pull Request* to the
   [*Unsupported-Contrib-OpenFOAM*][user] user account.
9. The contribution will be assessed against the criteria described in
   [*Contributing OpenFOAM Code*][] (above). The
   pull request will be accepted if those criteria are satisfied; otherwise the
   reasons for rejection will be provided.

[*Contributing OpenFOAM Code*]: #contributing-openfoam-code

Migration to OpenFOAM
---------------------
ESI-OpenCFD and any Contributor(s) may agree to migrate their code from the
Unsupported Contributions Repository to the official OpenFOAM release, for
distribution by the OpenFOAM Foundation. The Foundation maintain the sole
copyright of all OpenFOAM code it distributes, to be able to enforce the GPL
effectively, as [advocated by the Free Software Foundation][assign]. Therefore,
migration of code is conditional on the authors transferring copyright to the
OpenFOAM Foundation (or signing a licence agreement to the Foundation in
countries where copyright cannot be transferred from the author). Contributing
authors will be duly acknowledged in the source code files to which they
contributed.

[assign]: http://www.gnu.org/licenses/why-assign.html
