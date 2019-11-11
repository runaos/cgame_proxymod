/*
  ==============================
  Written by id software, nightmare and hk of mdd
  This file is part of mdd client proxymod.

  mdd client proxymod is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  mdd client proxymod is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with mdd client proxymod.  If not, see <http://www.gnu.org/licenses/>.
  ==============================
  Note: mdd client proxymod contains large quantities from the quake III arena source code
*/
#include "cg_utils.h"

#include "cg_cvar.h"
#include "cg_vm.h"

snapshot_t const* getSnap(void)
{
  static snapshot_t tmp;
  uint32_t          curSnapNum;
  uint32_t          servertime;

  g_syscall(CG_GETCURRENTSNAPSHOTNUMBER, &curSnapNum, &servertime);
  g_syscall(CG_GETSNAPSHOT, curSnapNum, &tmp);

  return &tmp;
}

playerState_t const* getPs(void)
{
  if (!cvar_getInteger("g_synchronousClients"))
  {
    return (playerState_t const*)((intptr_t)g_VM.dataSegment + (intptr_t)cvar_getInteger("mdd_pps_offset"));
  }
  else
  {
    return &getSnap()->ps;
  }
}

uint32_t getTime(void)
{
  return g_syscall(CG_MILLISECONDS);
}
