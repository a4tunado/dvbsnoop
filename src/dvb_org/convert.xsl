<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" />
<xsl:template match="/">
      <xsl:for-each select="//div[@id='alloc_table']/table/tr[td]">
      { <xsl:value-of select="translate(normalize-space(td[1]), '&#xa0;-', ' ,')"/>,
        "<xsl:value-of select="translate(td[2], '&quot;', &quot;'&quot;)">
        </xsl:value-of> - <xsl:value-of select="translate(td[5], '&quot;', &quot;'&quot;)">
        </xsl:value-of> - <xsl:value-of select="translate(td[3], '&quot;', &quot;'&quot;)">
        </xsl:value-of>"
      },</xsl:for-each>
</xsl:template>
</xsl:stylesheet>
